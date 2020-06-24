#!/bin/bash

colmap=/root/misc_codes/colmap/colmap-bin/bin/colmap
workspace=/root/test_result/colmap_result/${1}
images=${workspace}/images
database_path=${workspace}/database.db
sparse_path=${workspace}/sparse
dense_path=${workspace}/dense
maxsize=2000
maxfeature=8192

intrinsic_fp="2759.48,2764.16,1520.69,1006.81" # fountain-p11
intrinsic_tp="1520.40,1525.90,302.32,246.87" # temple
intrinsic_dtu="2892.33,2883.17,823.21,619.07" # all dtu dataset
intrinsic_tanks=""
intrinsic=${intrinsic_dtu}

# --ImageReader.camera_params ${intrinsic} \
${colmap} feature_extractor \
        --database_path ${database_path} \
        --image_path ${images} \
        --ImageReader.camera_model PINHOLE \
        --ImageReader.camera_params ${intrinsic} \
        --ImageReader.single_camera 1 \
        --SiftExtraction.max_image_size ${maxsize} \
        --SiftExtraction.max_num_features ${maxfeature}

${colmap} exhaustive_matcher --database_path ${database_path} \
        --SiftMatching.guided_matching 0

mkdir ${sparse_path}
${colmap} mapper --database_path ${database_path} \
        --image_path ${images} \
        --output_path ${sparse_path} \
        --Mapper.ba_refine_principal_point false

mkdir ${dense_path} &&
${colmap} image_undistorter --image_path ${images} \
        --input_path ${sparse_path}/0 \
        --output_path ${dense_path} \
        --output_type COLMAP \
        --max_image_size ${maxsize} &&

${colmap} patch_match_stereo --workspace_path ${dense_path} \
        --workspace_format COLMAP \
        --PatchMatchStereo.max_image_size ${maxsize} \
        --PatchMatchStereo.window_radius 9 \
        --PatchMatchStereo.geom_consistency 1 \
        --PatchMatchStereo.filter_min_ncc 0.07 &&

${colmap} stereo_fusion --workspace_path ${dense_path} \
        --input_type geometric \
        --output_path ${dense_path}/fused.ply &&

${colmap} poisson_mesher --input_path ${dense_path}/fused.ply \
        --output_path ${dense_path}/meshed-poisson.ply

${colmap} delaunay_mesher --input_path ${dense_path} \
        --input_type dense \
        --output_path ${dense_path}/meshed-delaunay.ply

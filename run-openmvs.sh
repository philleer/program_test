#!/bin/bash

workspace_path=/root/test_result/openmvs_result/${1}
image_dir=${workspace_path}/images
recon_dir=${workspace_path}/reconstruct
match_dir=${recon_dir}/matches
openmvg=/root/misc_codes/openMVG/openmvg-bin/bin
openmvs=/root/misc_codes/openMVS/openmvs-build/bin

maxres=6400
minres=480

intrinsic_fp="2759.48;0;1520.69;0;2764.16;1006.81;0;0;1" # fountain-p11
intrinsic_tp="1520.40;0;302.32;0;1525.90;246.87;0;0;1" # temple
intrinsic_eth_pipe="3430.27;0;3119.2;0;3429.23;2057.75;0;0;1" # eth3d pipes
intrinsic_dtu="2892.33;0;823.21;0;2883.17;619.07;0;0;1" # for all dtu datasets
intrinsic_tanks="2304.00;0;960;0;2304.00;540;0;0;1" # Manually set intrinsic
intrinsic=${intrinsic_dtu}

mkdir ${recon_dir} && mkdir ${match_dir}
${openmvg}/openMVG_main_SfMInit_ImageListing -i ${image_dir} -o ${match_dir} \
        --camera_model 1 \
        --intrinsics ${intrinsic} \
        --group_camera_model 1

${openmvg}/openMVG_main_ComputeFeatures -i ${match_dir}/sfm_data.json \
        --outdir ${match_dir} \
        --describerPreset HIGH

${openmvg}/openMVG_main_ComputeMatches -i ${match_dir}/sfm_data.json \
        --out_dir ${match_dir} \
        --nearest_matching_method ANNL2

${openmvg}/openMVG_main_IncrementalSfM -i ${match_dir}/sfm_data.json \
        --matchdir ${match_dir} \
        --outdir ${recon_dir} \
        --camera_model 1 \
        --refineIntrinsics NONE
        # --refineIntrinsics "ADJUST_FOCAL_LENGTH|ADJUST_PRINCIPAL_POINT"

${openmvg}/openMVG_main_ComputeSfM_DataColor -i ${recon_dir}/sfm_data.bin \
        -o ${recon_dir}/colorized.ply

${openmvg}/openMVG_main_ComputeStructureFromKnownPoses -i ${recon_dir}/sfm_data.bin \
        --match_dir ${match_dir} \
        --match_file ${match_dir}/matches.f.bin \
        --output_file ${recon_dir}/robust.bin

${openmvg}/openMVG_main_ComputeSfM_DataColor -i ${recon_dir}/robust.bin \
        -o ${recon_dir}/robust_colorized.ply

# outfile is the file name to save converted result
# outdir is the path to save undistorted images
${openmvg}/openMVG_main_openMVG2openMVS --sfmdata ${recon_dir}/sfm_data.bin \
        --outfile ${recon_dir}/scene.mvs \
        --outdir ${recon_dir}

${openmvs}/DensifyPointCloud --working-folder ${recon_dir} \
        -i ${recon_dir}/scene.mvs \
        --max-resolution=${maxres} \
        --min-resolution=${minres} \
        --number-views=6
# free-space-support is for textureless region
${openmvs}/ReconstructMesh --working-folder ${recon_dir} \
        -i ${recon_dir}/scene_dense.mvs \
        --free-space-support 1

${openmvs}/RefineMesh --working-folder ${recon_dir} \
        -i ${recon_dir}/scene_dense_mesh.mvs \
        --min-resolution ${minres} \
        --max-views 9 \
        --scales 5 \
        --planar-vertex-ratio 5

${openmvs}/TextureMesh --working-folder ${recon_dir} \
        -i ${recon_dir}/scene_dense_mesh.mvs \
        --min-resolution ${minres} \
        --cost-smoothness-ratio 0.3

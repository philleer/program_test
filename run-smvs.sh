#!/bin/bash

workspace_path=/root/test_result/smvs_result
image_dir=${workspace_path}/${1}
scene_dir=${workspace_path}/${2}
mve=/root/misc_codes/mve/apps
smvs=/root/misc_codes/smvs/smvsrecon

maxpixel=2000000

intrinsic_fp="2759.48,0,0,0.4950,0.4916,0.9983" # fountain-p11
intrinsic_tp="1520.40,0,0,0.4724,0.5143,0.9964" # temple
intrinsic_eth_pipe="3430.27,0,0,0.5015,0.4969,1.0003" # eth3d pipes
intrinsic_dtu="2892.33,0,0,0.5145,0.5159,1.0032" # dtu dataset
intrinsic_tanks="2304.00,0,0,0.5,0.5,1.0000" # Manually set intrinsic
intrinsic=${intrinsic_fp}

${mve}/makescene/makescene --original \
        --images-only ${image_dir} \
        --max-pixels=${maxpixel} \
        --init-intrinsics=${intrinsic} \
        ${scene_dir} &&

${mve}/sfmrecon/sfmrecon --max-pixels=${maxpixel} \
        --fixed-intrinsics \
        --verbose-ba ${scene_dir} &&

${smvs} ${scene_dir} &&

${mve}/fssrecon/fssrecon ${scene_dir}/pset-L0.ply ${scene_dir}/surface-L0.ply &&

${mve}/meshclean/meshclean --threshold=8.0 --delete-scale \
       ${scene_dir}/surface-L0.ply \
       ${scene_dir}/surface-clean.ply

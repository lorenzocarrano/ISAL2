#!bin/bash

#reading source files from common, adder and multpiplier directories
read_file -format vhdl /home/isa21_2021_2022/labs/ISAL2/fpuvhdl/common/{fpnormalize_fpnormalize,fpround_fpround,packfp_packfp,unpackfp_unpackfp}.vhd

read_file -format vhdl /home/isa21_2021_2022/labs/ISAL2/fpuvhdl/adder/{fpadd_normalize_struct,fpadd_pipeline,fpadd_stage1_struct,fpadd_stage2_struct,fpadd_stage3_struct,fpadd_stage4_struct,fpadd_stage5_struct,fpadd_stage6_struct,fpalign_struct,fpinvert_fpinvert,fplzc_fplzc,fpselcomplement_fpselcomplement,fpswap_fpswap}.vhd

read_file -format vhdl /home/isa21_2021_2022/labs/ISAL2/fpuvhdl/multiplier/{fpmul_pipeline,fpmul_single_cycle,fpmul_stage1_struct,fpmul_stage2_struct,fpmul_stage3_struct,fpmul_stage4_struct,fd,register}.vhd
############################################

#analyzing those files
analyze -library WORK -format vhdl /home/isa21_2021_2022/labs/ISAL2/fpuvhdl/common/{fpnormalize_fpnormalize,fpround_fpround,packfp_packfp,unpackfp_unpackfp}.vhd

analyze -library WORK -format vhdl /home/isa21_2021_2022/labs/ISAL2/fpuvhdl/adder/{fpadd_normalize_struct,fpadd_pipeline,fpadd_stage1_struct,fpadd_stage2_struct,fpadd_stage3_struct,fpadd_stage4_struct,fpadd_stage5_struct,fpadd_stage6_struct,fpalign_struct,fpinvert_fpinvert,fplzc_fplzc,fpselcomplement_fpselcomplement,fpswap_fpswap}.vhd

analyze -library WORK -format vhdl /home/isa21_2021_2022/labs/ISAL2/fpuvhdl/multiplier/{fpmul_pipeline,fpmul_single_cycle,fpmul_stage1_struct,fpmul_stage2_struct,fpmul_stage3_struct,fpmul_stage4_struct,fd,register}.vhd
############################################

#synthesis commands:
set power_preserve_rtl_hier_names true
elaborate FPmul -arch pipeline -lib WORK > ./elaborate.txt
uniquify
link
create_clock -name MY_CLK -period 0 CLK
set_dont_touch_network MY_CLK
set_clock_uncertainty 0.07 [get_clocks MY_CLK]
set_input_delay 0.5 -max -clock MY_CLK [remove_from_collection [all_inputs] CLK]
set_output_delay 0.5 -max -clock MY_CLK [all_outputs]
set OLOAD [load_of NangateOpenCellLibrary/BUF_X4/A]
set_load $OLOAD [all_outputs]
compile
report_timing > report_timing.txt
report_area > report_area.txt
ungroup -all -flatten
change_names -hierarchy -rules verilog
write_sdf ../netlist/FPmul.sdf
write -f verilog -hierarchy -output ../netlist/FPmul.v
write_sdc ../netlist/FPmul.sdc
quit

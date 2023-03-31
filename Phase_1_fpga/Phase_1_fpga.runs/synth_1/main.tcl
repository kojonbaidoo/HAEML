# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
create_project -in_memory -part xc7a35tcpg236-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.cache/wt [current_project]
set_property parent.project_path C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property ip_output_repo c:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_vhdl -library xil_defaultlib {
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/configuration_pack.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/MMSU_1.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/MMSU_3.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/MMSU_5.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/PRNG_8_bit.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/VMU_1.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/VMU_3.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/VMU_5.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/VRELU_2.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/VRELU_4.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/VRELU_6.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/binto7seg.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/clockdelay.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/communication_module.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/fourtosixteendecoder.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/output_comparator.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/relu.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/rounding_bits_generator.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/weight_store.vhd
  C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/sources_1/new/main.vhd
}
# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/constrs_1/new/basys_3_phase_1.xdc
set_property used_in_implementation false [get_files C:/Users/Kojo/OneDrive/Ashesi/Capstone/Implementation/HAEML/Phase_1_fpga/Phase_1_fpga.srcs/constrs_1/new/basys_3_phase_1.xdc]

set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top main -part xc7a35tcpg236-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef main.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file main_utilization_synth.rpt -pb main_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]

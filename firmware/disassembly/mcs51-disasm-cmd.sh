#!/usr/bin/env bash
SDCC_DIR=~/git/sdcc-4.0.0

perl -w $SDCC_DIR/support/scripts/mcs51-disasm.pl -I . -M SH68F83.h -fl -rj --const-area 0x007E 0x0529 --const-area 0x0815 0x974 --const-area 0x3F2C 0x3FFF --name-list fw_ansi.namelist -v 5 fw_ansi.hex > fw_ansi.mcs51

perl -w $SDCC_DIR/support/scripts/mcs51-disasm.pl -I . -M SH68F83.h -fl -rj --const-area 0x3F2C 0x3FFF --name-list ssp.namelist -v 5 ssp.hex > ssp.mcs51

#perl -w $SDCC_DIR/support/scripts/mcs51-disasm.pl -I . -M SH68F83.h -fl -rj --const-area 0x007E 0x0529 --const-area 0x0815 0x974 --const-area 0x3F2C 0x3FFF --name-list mcs51-disasm.namelist -v 5 fw_tp_update.hex > fw_tp_update.mcs51

#perl -w $SDCC_DIR/support/scripts/mcs51-disasm.pl -I $SDCC_DIR/device/include/mcs51 -M 8051.h -fl -rj scratch/tpfw.hex | less

#Usage: mcs51-disasm.pl [options] <hex file>
#
#    Options are:
#
#        -M|--mcu <header.h>
#
#            Header file of the MCU.
#
#        -I|--include <path to header>
#
#            Path of the header files of MCS51 MCUs. (Default: )
#
#        --map-file <file.map>
#
#            The map file belonging to the input hex file. (optional)
#
#        -r|--rom-size <size of program memory>
#
#            Defines size of the program memory. (Default 65536 bytes.)
#
#        --const-area <start address> <end address>
#
#            Designates a constant area (jumptables, texts, etc.), where data is
#            stored happen. The option may be given more times, that to select
#            more areas at the same time. (optional)
#
#        -hc|--hex-constant
#
#            The constants only shows in hexadecimal form. Otherwise if possible,
#            then shows all in character form.
#
#        -as|--assembly-source
#
#            Generates the assembly source file. (Eliminates before the instructions
#            visible address, hex codes and besides replaces the pseudo Rn<#x>
#            register names.) Emits global symbol table, SFR table, Bits table, etc.
#
#        -rj|--recognize-jump-tables
#
#            Recognizes the jump tables.
#
#        -fl|--find-lost-labels
#
#            Finds the "lost" labels. These may be found such in program parts,
#            which are directly not get call.
#
#        --name-list <list_file>
#
#            The file contains list of names. They may be: Names of variables and
#            names of labels. For example:
#
#                [BIT]
#                0x07:bit_variable
#                ..
#                ..
#                ..
#                [RAM]
#                0x31:direct_ram_variable
#                ..
#                ..
#                ..
#                [IRAM]
#                0x91:indirect_ram_variable
#                ..
#                ..
#                ..
#                [XRAM]
#                0x208:external_ram_variable
#                ..
#                ..
#                ..
#                [ROM]
#                0x05FC:function_or_label
#                ..
#                ..
#                ..
#
#            The contents of list override the names from map file.
#
#        -ne|--no-explanations
#
#            Eliminates after the instructions visible explaining texts.
#
#        -v <level> or --verbose <level>
#
#            It provides information on from the own operation.
#            Possible value of the level between 0 and 10. (default: 0)
#
#        -h|--help
#
#            This text.
#

# Address | Name                 | Description
# 0x0039    ?C?WAIT18             
# 0x003a    ?C?WAIT17             
# 0x003c    ?C?WAIT15             
# 0x003d    ?C?WAIT14             
# 0x003f    ?C?WAIT12             
# 0x0040    ?C?WAIT11             
# 0x11fd   [?C_START]             
# 0x177c    ?C?CLDPTR              char (8-bit) load from general pointer
# 0x1795    ?C?CLDOPTR             char (8-bit) load from general pointer with offset
# 0x17c2    ?C?CSTOPTR             char (8-bit) store to general pointer with offset
# 0x17e4    ?C?ICALL              
# 0x17e8    ?C?ICALL2             
# 0x260c    ?C?WAIT18             
# 0x260d    ?C?WAIT17             
# 0x260f    ?C?WAIT15             
# 0x2610    ?C?WAIT14             
# 0x2612    ?C?WAIT12             
# 0x2613    ?C?WAIT11             
# 0x267b   (MAIN)                 

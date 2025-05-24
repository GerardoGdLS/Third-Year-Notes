#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="D:/Fall 2024/ENSF460/Lab 3/UART2.c" "D:/Fall 2024/ENSF460/Lab 3/assignment3_main.c" "D:/Fall 2024/ENSF460/Lab 3/clkChange.c" "D:/Fall 2024/ENSF460/Lab 3/IOs.c" "D:/Fall 2024/ENSF460/Lab 3/TimeInterval.c" "D:/Fall 2024/ENSF460/Lab 3/main.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1486900562/UART2.o ${OBJECTDIR}/_ext/1486900562/assignment3_main.o ${OBJECTDIR}/_ext/1486900562/clkChange.o ${OBJECTDIR}/_ext/1486900562/IOs.o ${OBJECTDIR}/_ext/1486900562/TimeInterval.o ${OBJECTDIR}/_ext/1486900562/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1486900562/UART2.o.d ${OBJECTDIR}/_ext/1486900562/assignment3_main.o.d ${OBJECTDIR}/_ext/1486900562/clkChange.o.d ${OBJECTDIR}/_ext/1486900562/IOs.o.d ${OBJECTDIR}/_ext/1486900562/TimeInterval.o.d ${OBJECTDIR}/_ext/1486900562/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1486900562/UART2.o ${OBJECTDIR}/_ext/1486900562/assignment3_main.o ${OBJECTDIR}/_ext/1486900562/clkChange.o ${OBJECTDIR}/_ext/1486900562/IOs.o ${OBJECTDIR}/_ext/1486900562/TimeInterval.o ${OBJECTDIR}/_ext/1486900562/main.o

# Source Files
SOURCEFILES=D:/Fall 2024/ENSF460/Lab 3/UART2.c D:/Fall 2024/ENSF460/Lab 3/assignment3_main.c D:/Fall 2024/ENSF460/Lab 3/clkChange.c D:/Fall 2024/ENSF460/Lab 3/IOs.c D:/Fall 2024/ENSF460/Lab 3/TimeInterval.c D:/Fall 2024/ENSF460/Lab 3/main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24F16KA101
MP_LINKER_FILE_OPTION=,--script=p24F16KA101.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1486900562/UART2.o: D:/Fall\ 2024/ENSF460/Lab\ 3/UART2.c  .generated_files/flags/default/32af8fe9c90bd794d4d2a73c78a010306ce913be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/UART2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/UART2.c"  -o ${OBJECTDIR}/_ext/1486900562/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/UART2.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/assignment3_main.o: D:/Fall\ 2024/ENSF460/Lab\ 3/assignment3_main.c  .generated_files/flags/default/7c4d4a6ab0f665ab8d7adbc9b4f2811b4bc654e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/assignment3_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/assignment3_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/assignment3_main.c"  -o ${OBJECTDIR}/_ext/1486900562/assignment3_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/assignment3_main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/clkChange.o: D:/Fall\ 2024/ENSF460/Lab\ 3/clkChange.c  .generated_files/flags/default/cff3ee94958d826965d073a87ef2d7ea4ceff00a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/clkChange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/clkChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/clkChange.c"  -o ${OBJECTDIR}/_ext/1486900562/clkChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/clkChange.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/IOs.o: D:/Fall\ 2024/ENSF460/Lab\ 3/IOs.c  .generated_files/flags/default/cab2c2a261841b8dfffdd70b2f6c07ec6d2cc1ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/IOs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/IOs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/IOs.c"  -o ${OBJECTDIR}/_ext/1486900562/IOs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/IOs.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/TimeInterval.o: D:/Fall\ 2024/ENSF460/Lab\ 3/TimeInterval.c  .generated_files/flags/default/548a20535c639737c18f807212f2d37f36e522d1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/TimeInterval.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/TimeInterval.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/TimeInterval.c"  -o ${OBJECTDIR}/_ext/1486900562/TimeInterval.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/TimeInterval.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/main.o: D:/Fall\ 2024/ENSF460/Lab\ 3/main.c  .generated_files/flags/default/982a70ac7364ba2d1fbd295517d6cde90d693a01 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/main.c"  -o ${OBJECTDIR}/_ext/1486900562/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/main.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/_ext/1486900562/UART2.o: D:/Fall\ 2024/ENSF460/Lab\ 3/UART2.c  .generated_files/flags/default/c391a6604dc8ac296a209a4f88e87c8f14cb735d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/UART2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/UART2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/UART2.c"  -o ${OBJECTDIR}/_ext/1486900562/UART2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/UART2.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/assignment3_main.o: D:/Fall\ 2024/ENSF460/Lab\ 3/assignment3_main.c  .generated_files/flags/default/bf0a389ea32555ee41053e69060c6570942dcc30 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/assignment3_main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/assignment3_main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/assignment3_main.c"  -o ${OBJECTDIR}/_ext/1486900562/assignment3_main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/assignment3_main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/clkChange.o: D:/Fall\ 2024/ENSF460/Lab\ 3/clkChange.c  .generated_files/flags/default/210d4a4568368445af548623eacb09ca4599a0fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/clkChange.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/clkChange.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/clkChange.c"  -o ${OBJECTDIR}/_ext/1486900562/clkChange.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/clkChange.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/IOs.o: D:/Fall\ 2024/ENSF460/Lab\ 3/IOs.c  .generated_files/flags/default/f87aaf0e26209a4da4a2a39200aa913e0d9619e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/IOs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/IOs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/IOs.c"  -o ${OBJECTDIR}/_ext/1486900562/IOs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/IOs.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/TimeInterval.o: D:/Fall\ 2024/ENSF460/Lab\ 3/TimeInterval.c  .generated_files/flags/default/3e499101921966ed24d0daea5566c30be54386d0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/TimeInterval.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/TimeInterval.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/TimeInterval.c"  -o ${OBJECTDIR}/_ext/1486900562/TimeInterval.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/TimeInterval.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/_ext/1486900562/main.o: D:/Fall\ 2024/ENSF460/Lab\ 3/main.c  .generated_files/flags/default/a640fa4147591806e754b05a6d0117aaa72e182c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1486900562" 
	@${RM} ${OBJECTDIR}/_ext/1486900562/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1486900562/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  "D:/Fall 2024/ENSF460/Lab 3/main.c"  -o ${OBJECTDIR}/_ext/1486900562/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/_ext/1486900562/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Lab_3.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Lab_3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Lab_3.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif

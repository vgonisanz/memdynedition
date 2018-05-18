#!/bin/bash

#
# This script is a sample
#
# Author: Víctor Goñi <vgonisanz@gmail.com>
#

#
# Configuration
#
#set +x             # Uncomment to debug
PRINT_SCRIPT="${BASH_SOURCE%/*}/print.inc"   # This script require print include at common relative folder to work propertly. Change path if needed.
MAX_ARGS=1
TMP_DIR="${BASH_SOURCE%/*}/tmp"
INPUT_PIPE="${TMP_DIR}/input.pipe"
OUTPUT_LOG="${TMP_DIR}/output.0"

#
# Variables
#
BASIC_SAMPLE=
PID=

#
# Installing Traps
#
# Possible args: SIGQUIT, SIGTSTP, SIGTTIN, SIGTTOU, SIGINT, SIGTERM
#

trap f_ctrl_c SIGINT
trap f_ctrl_c SIGTERM

#
# Functions
#
function f_usage()
{
    echo ""
    LOGI "Usage: $0 -b BASIC_SAMPLE_BIN"
    LOGI "Output will be places in ${TMP_DIR}. This directory is deleted in new executions!"
    echo ""
    exit 1
}

function f_handle_error()
{
    local msg=$1
    LOGE "${msg}"
    exit 2
}

function f_create_tmp()
{
    if [ -d "${TMP_DIR}" ]; then
        echo "Removing ${TMP_DIR}"
        rm -fr ${TMP_DIR}
    fi
    mkdir -p ${TMP_DIR}
    mkfifo ${INPUT_PIPE}
}

function f_clean_up()
{
    [[ ! -z ${PID+x} ]] && LOGI "Killing ${PID}" && kill -9 ${PID}
}

function f_ctrl_c()
{
    f_clean_up
    LOGOK "Control+C sequence pressed..."
    exit 0
}

function f_check_arguments()
{
    [ ! -f ${BASIC_SAMPLE} ] && f_handle_error "BASIC_SAMPLE does not exist"
}

function f_launch_program()
{
    (tail -f ${INPUT_PIPE}) | ${BASIC_SAMPLE} > ${OUTPUT_LOG} &
    PID=$(pidof ${BASIC_SAMPLE})
    [[ -z ${PID+x} ]] && f_clean_up && f_handle_error "PID is empty"
    LOGI "Running ${BASIC_SAMPLE} with ID ${PID}"
}

function f_while_true()
{
    LOGI "Info message: Use Cntl + C to exit!"
    while true; do
      # Nothing, use ctrl_c
      sleep 1
    done
}

#
# Main
#
[ -f ${PRINT_SCRIPT} ] && source ${PRINT_SCRIPT}

while getopts "hb:" o; do
    case "${o}" in
        h)
            f_usage
            ;;
        b)
            BASIC_SAMPLE=${OPTARG}
            ;;
    esac
done

shift $((OPTIND-1))

f_check_arguments
f_create_tmp
f_launch_program
f_while_true

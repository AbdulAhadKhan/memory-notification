# import settings from config file
source ./config.sh

function print_and_log() {
    echo -e "$1"
    echo -e "$1" >> log
}
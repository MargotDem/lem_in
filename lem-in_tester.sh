#!/bin/bash

#add system("leaks lem-in >> leaks.txt") before return in main
#add system("leaks lem-in >> error_leaks.txt") before exit(1)

#./lem-in < test_maps/augment_1.map > /dev/null
#./lem-in < test_maps/valid_3hash_comment.map > /dev/null
#./lem-in < test_maps/invalid_end.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_coord.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_double_ant_number.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_double_start.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_empty_line.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_roomname#.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_room_name_with_dash.map > /dev/null 2>&1
#./lem-in < test_maps/invalid_room_name_L.map > /dev/null 2>&1
# wait

noir='\e[0;30m'
gris='\e[1;30m'
rougefonce='\e[0;31m'
rose='\e[1;31m'
vertfonce='\e[0;32m'
vertclair='\e[1;32m'
orange='\e[0;33m'
jaune='\e[1;33m'
bleufonce='\e[0;34m'
bleuclair='\e[1;34m'
violetfonce='\e[0;35m'
violetclair='\e[1;35m'
cyanfonce='\e[0;36m'
cyanclair='\e[1;36m'
grisclair='\e[0;37m'
blanc='\e[1;37m'

neutre='\e[0;m'
underline='\e[4m'
bold='\033[1m'
italic='\e[3m'

pwd=$(pwd)

declare -a map
declare -a your_line
declare -a ref_line
declare -a ref_leaks

clean () {
    if [ -e $pwd/leaks ];then
        rm -rf $pwd/leaks
    fi
    if [ -e $pwd/map_output ];then
        rm -rf $pwd/map_output
    fi
}

save_leaks () {
    if [ -e $pwd/int_leaks.txt ];then
        int_leaks=$(grep "leaked bytes" $pwd/int_leaks.txt | cut -d ' ' -f 3)
        if [ $int_leaks -ne 0 ]; then
            mkdir -p $pwd/leaks/int
            cp $pwd/int_leaks.txt $pwd/leaks/int/$strmap
        fi
    fi
    if [ -e $pwd/exit_s_leaks.txt ];then
        exit_solver=$(grep "leaked bytes" $pwd/exit_s_leaks.txt | cut -d ' ' -f 3)
        if [ $exit_solver -ne 0 ]; then
            mkdir -p $pwd/leaks/exit_solver
            cp $pwd/exit_p_leaks.txt $pwd/leaks/exit_solver/$strmap
        fi
    fi
    if [ -e $pwd/exit_p_leaks.txt ];then
        exit_parsing=$(grep "leaked bytes" $pwd/exit_p_leaks.txt | cut -d ' ' -f 3)
        if [ $exit_parsing -ne 0 ]; then
            mkdir -p $pwd/leaks/exit_parsing
            cp $pwd/exit_p_leaks.txt $pwd/leaks/exit_parsing/$strmap
        fi
    fi
}

set_data_leaks () {
    # process_line=$(grep "leaked bytes" $pwd/exit_leaks.txt)
    # leaks=$(grep "leaked bytes" $pwd/exit_leaks.txt | cut -d ' ' -f 3)
    process_line=$(grep "leaked bytes" $1)
    leak=$(grep "leaked bytes" $1 | cut -d ' ' -f 3)
}

save_arr () {
    # map=( "${map[@]}" "$strmap" )
    # your_line=( "${your_line[@]}" "ERROR" )
    # ref_line=( "${ref_line[@]}" "ERROR" )
    # leak=( "${ref_leaks[@]}" "$leaks" )
    map=( "${map[@]}" "$1" )
    your_line=( "${your_line[@]}" "$2" )
    ref_line=( "${ref_line[@]}" "$3" )
    leak=( "${ref_leaks[@]}" "$4" )
}


display_error () {
    printf "We found an Error in $1\n"
    # printf "We found "
    # if [ $leak -ne 0 ]; then
    #     printf "${rougefonce}${bold}"
    #     mkdir -p $pwd/leaks
    #     cp $pwd/leaks.txt $pwd/leaks/$strmap
    # else
    #     printf "${vertfonce}${bold}"   
    # fi
    # printf "$leak${neutre} leaks from your program.\n"
    # printf "\t${italic}$process_line${neutre}\n\n"
}

set_data_line () {
        line_required=$(grep "lines required" $1 | cut -d' ' -f 8 | head -n 1)
        line_founded=$(grep "^L" $1 | wc -l | awk '{gsub(/^[ \t]+| [ \t]+$/,""); print$0, ""}')
}

display () {
    printf "In map $1\n"
    printf "Your returned ${orange}${underline}${bold}$2${neutre} lines and the required line is ${cyanfonce}${underline}${bold}$3${neutre}\n"
    max=5
    max=$(($3 + 5))
    min=$(($3 - 5))
    printf "You have a diffence of "
    if [ $2 -ge $max ]; then
        printf "${rougefonce}${bold}"
    elif [ $2 -le $min ]; then
        printf "${rougefonce}${bold}"
    else
        printf "${vertfonce}${bold}"
    fi
    printf "$diff${neutre} lines.\n"
}

display_leaks () {
    printf "We found "
    if [ "$1" -ne "0" ]; then
        printf "${rougefonce}${bold}"
        mkdir -p $pwd/leaks
        cp $pwd/leaks.txt $pwd/leaks/$strmap
    else
        printf "${vertfonce}${bold}"   
    fi
    printf "$1${neutre} leaks from your program.\n"
    printf "\t${italic}$2${neutre}\n\n"
}
clean

mkdir -p $pwd/map_output

for MAP in $(find ./test_maps -type f);
do
    result=$(grep ".txt" <<< "$MAP")
    if [ -n "$result" ]; then
        strmap=$(echo $result | rev | cut -d'/' -f 1| rev)
        ./lem-in < $MAP &> $pwd/map_output/$strmap
        save_leaks
        error=$(grep -i "ERROR" $pwd/map_output/$strmap)
        if [ $error ]; then
            set_data_leaks $pwd/exit_leaks.txt
            save_arr "$strmap" "Error" "Error" "$leak"
            if [ "$1" = '-v' ]; then
                display_error "$strmap"
                display_leaks $leak "$process_line"
            fi
        else
            set_data_line "$pwd/map_output/$strmap"
            if [[ $line_required ]]; then
                if (( $line_required == $line_founded ));then
                    diff=0
                else
                    if (( $line_required > $line_founded ));then
                        diff=$(($line_required - $line_founded))
                    else
                        diff=$(($line_founded - $line_required))
                    fi
                fi
            else
                line_required=0
                diff=0
            fi
            set_data_leaks $pwd/leaks.txt
            if [ "$1" = '-v' ]; then
                display $strmap $line_founded $line_required
                display_leaks $leak "$process_line"
            fi
            save_arr "$strmap" "$line_founded" "$line_required" "$leak"
        fi
    fi
done
i=0
size=${#your_line[*]}
printf "Summary: \n"
printf "MAP NAME| SOLUTION | REQUIRED | LEAKS |\n"
while [ "$i" -lt "$size" ]
do
printf "${map[i]} | ${your_line[i]} | ${ref_line[i]} | ${leaks[i]} | OK\n"
i=$(( i + 1 ))
done
rm -rf exit_p_leaks.txt
rm -rf exit_s_leaks.txt
rm -rf exit_leaks.txt
rm -rf int_leaks.txt
rm -rf leaks.txt
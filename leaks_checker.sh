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
mkdir -p $pwd/map_output
declare -a map
declare -a your_line
declare -a ref_line
declare -a ref_leaks

for MAP in $(find ./test_maps -type f);
do
    result=$(grep -e ".txt" <<< "$MAP")
    if [ -n "$result" ]; then
        strmap=$(echo $result | rev | cut -d'/' -f 1| rev)
        ./lem-in < $MAP &> $pwd/map_output/$strmap
        error=$(grep -i "ERROR" $pwd/map_output/$strmap)
        if [ $error ]; then
            leaks=$(grep "leaked bytes" $pwd/leaks.txt | cut -d ' ' -f 3)
            map=( "${map[@]}" "$strmap" )
            your_line=( "${your_line[@]}" "ERROR" )
            ref_line=( "${ref_line[@]}" "ERROR" )
            leaks=( "${ref_leaks[@]}" "$leaks" )
            printf "We found an Error in ${strmap}\n\n"
        else
            line_required=$(grep "lines required" $pwd/map_output/$strmap | cut -d' ' -f 8 | head -n 1)
            line_founded=$(grep "^L" $pwd/map_output/$strmap | wc -l | awk '{gsub(/^[ \t]+| [ \t]+$/,""); print$0, ""}')
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
            process_line=$(grep "leaked bytes" $pwd/leaks.txt)
            leaks=$(grep "leaked bytes" $pwd/leaks.txt | cut -d ' ' -f 3)
            printf "In map $strmap\n"
            printf "Your returned ${orange}${underline}${bold}$line_founded${neutre}lines and the required line is ${cyanfonce}${underline}${bold}$line_required${neutre}\n"
            max=5
            max=$(($line_required + 5))
            min=$(($line_required - 5))
            printf "You have a diffence of "
            if [ $line_founded -ge $max ]; then
                printf "${rougefonce}${bold}"
            elif [ $line_founded -le $min ]; then
                printf "${rougefonce}${bold}"
            else
                printf "${vertfonce}${bold}"
            fi
            printf "$diff${neutre} lines.\n"
            printf "We found "
            if [ $leaks -ne 0 ]; then
                printf "${rougefonce}${bold}"
                mkdir -p $pwd/leaks
                cp $pwd/leaks.txt $pwd/leaks/$strmap
            else
                printf "${vertfonce}${bold}"   
            fi
            printf "$leaks${neutre} bytes leaked from your program.\n"
            printf "\t${italic}$process_line${neutre}\n\n"
            map=( "${map[@]}" "$strmap" )
            your_line=( "${your_line[@]}" "$line_founded" )
            ref_line=( "${ref_line[@]}" "$line_required" )
            leaks=( "${ref_leaks[@]}" "$leaks" )
        fi
    fi
done
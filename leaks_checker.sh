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

pwd=$(pwd)
mkdir -p $pwd/map_output
for MAP in $(find ./test_maps -type f);
do
    result=$(grep -e ".txt" <<< "$MAP")
    if [ -n "$result" ]; then
        strmap=$(echo $result | rev | cut -d'/' -f 1| rev)
        ./lem-in < $MAP &> $pwd/map_output/$strmap
        line_required=$(grep "lines required" $pwd/map_output/$strmap | cut -d' ' -f 8 | head -n 1)
        line_founded=$(grep "^L" $pwd/map_output/$strmap | wc -l | awk '{gsub(/^[ \t]+| [ \t]+$/,""); print$0, ""}')
        if (( "$line_required" == "$line_founded" ));then
            diff=0
        else
            diff=$(($line_required-$line_founded))
        fi
        process_line=$(grep "leaked bytes" $pwd/leaks.txt)
        leaks=$(grep "leaked bytes" $pwd/leaks.txt | cut -d ' ' -f 3)
        printf "In map $strmap\n"
        printf "Your returned ${orange}${underline}$line_founded${neutre}lines and the required line is ${cyanfonce}${underline}$line_required${neutre}\n"
        di
        printf "You have a diffence of" 
        if [ "$line_founded" -gt "$line_required" ]; then
            printf "${vert}"
        fi
        printf "$diff${neutre} lines.\n"
        # You have a diffence of $diff lines.
        # We found $leaks bytes leaked from your programm.
        #     $process_line"


     
        

        # In map: MAPNAME
        #     you returned nomber of your line and the reference line is line required.
        #     the diffenre is diff
        #     Your program leaks bytes.




        
        # echo "In $strmap:" >> $pwd/leaks.resume
        # echo -e "\t" >> $pwd/leaks.resume
        # ret=$(grep "leaked" $pwd/error_leaks.txt) 
        # echo $ret >> $pwd/leaks.resume
    fi
done

# wait

# cat leaks.txt | grep "leaked bytes"
# cat error_leaks.txt | grep "leaked bytes"
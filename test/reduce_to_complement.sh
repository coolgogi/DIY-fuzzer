echo "reduce_to_complement split test case "

output=`../bin/complement input/jsondump input/complement_split_case.json 4`
answer="input/complement_split_case-2.json"

if [ "$answer" = "$output" ] ; then
    echo "correct answer"
else
    echo "wrong answer"
fi

echo "reduce_to_complement not split test case"

output=`../bin/complement input/jsondump input/complement_not_split_case.json 4`
answer="input/complement_not_split_case.json"

if [ "$answer" = "$output" ] ; then
    echo "correct answer"
else
    echo "wrong answer"
fi
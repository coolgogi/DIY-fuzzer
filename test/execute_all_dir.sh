echo "execute all directory runner test"

# rm ./output/answer.txt
# touch ./output/answer.txt
rm ./output/output.txt
touch ./output/output.txt

# ../bin/exec_test
../bin/main ./input/dir1/ ./output/output.txt

answer=`cat ./output/answer.txt`
output=`cat ./output/output.txt`

if [ "$answer" = "$output" ]; then
    echo "correct answer"
else
    echo "wrong answer"
fi


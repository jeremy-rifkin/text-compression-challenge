#!/bin/bash
#bin/markovhuffman sample.txt -o encoded.txt.mh -d table.mht
#bin/markovhuffman -x encoded.txt.mh -o sample_decoded.txt -e table.mht

function test {
	local input=$1
	local intermediate=$2
	local output=$3
	bin/z -c $input $intermediate
	bin/z -x $intermediate $output
	md5sum $input $output
	oldsize=`ls -l $input | awk '{print $5}'`
	newsize=`ls -l $intermediate | awk '{print $5}'`
	comp_ratio=`echo $newsize / $oldsize | bc -l`
	echo $comp_ratio
}

test data/sample.txt data/out.dat data/out.txt
test data/1984.txt data/out.dat data/out.txt

# dot -Tsvg graph.gz -o graph.svg

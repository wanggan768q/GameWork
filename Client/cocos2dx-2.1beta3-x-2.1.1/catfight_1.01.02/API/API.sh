

protoc -I=./ --cpp_out=./ UserInfo.proto



allname=`ls *.cc`
for name in $allname
do
mv $name ${name%.cc}.cpp
done

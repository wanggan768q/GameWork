

#protoc -I=./ --cpp_out=./ LanBattleData.proto
#protoc -I=./ --cpp_out=./ LanBattleReady.proto
#protoc -I=./ --cpp_out=./ LanCreateRoom.proto
#protoc -I=./ --cpp_out=./ LanJoinRoom.proto
#protoc -I=./ --cpp_out=./ LanRoomList.proto
#protoc -I=./ --cpp_out=./ LanSearchRoom.proto
#protoc -I=./ --cpp_out=./ LanSyncUserInfo.proto
#protoc -I=./ --cpp_out=./ LanUserInfo.proto 
#protoc -I=./ --cpp_out=./ LanStartBattle.proto
#protoc -I=./ --cpp_out=./ Icon.proto
#protoc -I=./ --cpp_out=./ LanBattleResult.proto
#protoc -I=./ --cpp_out=./ LanQuitRoom.proto

protoc -I=./ --cpp_out=./ MatchSearchStrength.proto
protoc -I=./ --cpp_out=./ GameSearchStrength.proto


allname=`ls *.cc`
for name in $allname
do
mv $name ${name%.cc}.cpp
done

#protoc -I=./ --java_out=./ Figure.proto
# To force update modules execute command:
# make -B

download: thirdparty/cotire.cmake thirdparty/PVS-Studio.cmake

thirdparty/cotire.cmake:
	wget -O thirdparty/cotire.cmake https://raw.githubusercontent.com/sakra/cotire/master/CMake/cotire.cmake

thirdparty/PVS-Studio.cmake:
	wget -O thirdparty/PVS-Studio.cmake https://raw.githubusercontent.com/viva64/pvs-studio-cmake-examples/master/PVS-Studio.cmake
	dos2unix thirdparty/PVS-Studio.cmake


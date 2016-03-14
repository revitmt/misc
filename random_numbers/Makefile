cpp_compiler         = icl
cpp_compiler_options = -c -MD -O3 -w
fortran_compiler         = ifort
fortran_compiler_options = -c -MD -O3 -w

boost_inc_path   = D:\Windows\lib\boost_1_60_0
boost_lib_path   = D:\Windows\lib\boost_1_60_0\stage\lib
cuda_inc_path    = D:\Windows\Programs\CudaToolkit\include
cuda_lib_path    = D:\Windows\Programs\CudaToolkit\lib\x64


all:	rnd_generator.obj main.obj main_fort.obj
	$(cpp_compiler) -o result main.obj rnd_generator.obj /link cuda.lib cudart.lib curand.lib /LIBPATH:$(cuda_lib_path) /LIBPATH:$(boost_lib_path)
	$(fortran_compiler) -o result_fort main_fort.obj rnd_generator.obj /link cuda.lib cudart.lib curand.lib /LIBPATH:$(cuda_lib_path) /LIBPATH:$(boost_lib_path)

# fort:	rnd_generator.obj main_fort.obj
# 	$(fortran_compiler) -o result main_fort.obj rnd_generator.obj /link cuda.lib cudart.lib curand.lib /LIBPATH:$(cuda_lib_path) /LIBPATH:$(boost_lib_path)

rnd_generator.obj:	rnd_generator.cpp 
	$(cpp_compiler) $(cpp_compiler_options) rnd_generator.cpp -I $(boost_inc_path) -I $(cuda_inc_path)

main_fort.obj:	main_fort.f90
	$(fortran_compiler) $(fortran_compiler_options) main_fort.f90

main.obj:	main.cpp
	$(cpp_compiler) $(cpp_compiler_options) main.cpp

clean:
	del *.obj *.exe
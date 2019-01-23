################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Builder.cpp \
../src/Cotainers.cpp \
../src/Draw.cpp \
../src/Floor.cpp \
../src/PedestrianSimulation.cpp \
../src/bmp.cpp 

O_SRCS += \
../src/PedestrianSimulation.o 

OBJS += \
./src/Builder.o \
./src/Cotainers.o \
./src/Draw.o \
./src/Floor.o \
./src/PedestrianSimulation.o \
./src/bmp.o 

CPP_DEPS += \
./src/Builder.d \
./src/Cotainers.d \
./src/Draw.d \
./src/Floor.d \
./src/PedestrianSimulation.d \
./src/bmp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0  -std=c++11 -lGL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



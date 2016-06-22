################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PTP_Client.c \
../src/af_packet.c \
../src/get_ip_hdr.c \
../src/get_ptp.c \
../src/get_udp_hdr.c \
../src/pf_packet.c \
../src/ptp_client_change.c \
../src/ptp_client_sent.c \
../src/ptp_client_set.c \
../src/ptp_packgen.c \
../src/ptp_packgen_share.c \
../src/ptpt_client_init.c 

OBJS += \
./src/PTP_Client.o \
./src/af_packet.o \
./src/get_ip_hdr.o \
./src/get_ptp.o \
./src/get_udp_hdr.o \
./src/pf_packet.o \
./src/ptp_client_change.o \
./src/ptp_client_sent.o \
./src/ptp_client_set.o \
./src/ptp_packgen.o \
./src/ptp_packgen_share.o \
./src/ptpt_client_init.o 

C_DEPS += \
./src/PTP_Client.d \
./src/af_packet.d \
./src/get_ip_hdr.d \
./src/get_ptp.d \
./src/get_udp_hdr.d \
./src/pf_packet.d \
./src/ptp_client_change.d \
./src/ptp_client_sent.d \
./src/ptp_client_set.d \
./src/ptp_packgen.d \
./src/ptp_packgen_share.d \
./src/ptpt_client_init.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



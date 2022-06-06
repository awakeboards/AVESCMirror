@echo off

set hw_version=2_3
set motor_types=AMOTOR ASTRO FOIL
set board_types=RV1 RV3 RVS FOIL
set shunt_types=SHUNT100 SHUNT200

del /s /q ".\build\*"

for /f "delims=" %%i in ('python .\scripts\version.py ./') do set sw_version=%%i

for %%a in (%motor_types%) do (
	for %%b in (%shunt_types%) do (
		for %%c in (%board_types%) do (
			del /s /q ".\build\obj\*"
			del /s /q ".\build\*_ChibiOS.*"
			echo AVESC_%hw_version%_%sw_version%_%%c_%%a_%%b
			make -j MTYPE=%%a STYPE=%%b BTYPE=%%c VTYPE=%sw_version%
			move ".\build\*_ChibiOS.bin" ".\build\VESC_AW_%hw_version%_%sw_version%_%%c_%%a_%%b.bin"
		)
	)
)

del /s /q ".\build\*RV1_FOIL*"
del /s /q ".\build\*RV3_FOIL*"
del /s /q ".\build\*RVS_FOIL*"

del /s /q ".\build\*RV1_AMOTOR*"

del /s /q ".\build\*RV3_ASTRO*"

del /s /q ".\build\*FOIL_ASTRO*"
del /s /q ".\build\*FOIL_AMOTOR*"

del /f /s /q ".\build\obj\*"
del /f /s /q ".\build\lst\*"
del /f /s /q ".\build\obj"
del /f /s /q ".\build\lst"
del /f /s /q ".\build\*_ChibiOS.*"

pause

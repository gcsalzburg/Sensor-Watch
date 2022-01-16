# Leave this line at the top of the file; it has all the watch library sources and includes.
TOP = ../..
include $(TOP)/make.mk

# If you add any other subdirectories with header files you wish to include, add them after ../
# Note that you will need to add a backslash at the end of any line you wish to continue, i.e.
# INCLUDES += \
#   -I../ \
#   -I../drivers/ \
#   -I../watch_faces/fitness/
INCLUDES += \
  -I../ \
  -I../watch_faces/ \
  -I../watch_faces/clock/ \
  -I../watch_faces/settings/ \
  -I../watch_faces/complications/ \
  -I../watch_faces/thermistor/ \
  -I../watch_faces/demos/ \
  -I../lib/TOTP-MCU/ \
  -I../lib/libnova/src/ \
  -I../lib/sunriset/ \

# If you add any other source files you wish to compile, add them after ../app.c
# Note that you will need to add a backslash at the end of any line you wish to continue, i.e.
# SRCS += \
#   ../movement.c \
#   ../drivers/lis2dh.c \
#   ../watch_faces/fitness/step_count_face.c
SRCS += \
  ../lib/TOTP-MCU/sha1.c \
  ../lib/TOTP-MCU/TOTP.c \
  ../lib/libnova/src/aberration.c \
  ../lib/libnova/src/airmass.c \
  ../lib/libnova/src/angular_separation.c \
  ../lib/libnova/src/apparent_position.c \
  ../lib/libnova/src/asteroid.c \
  ../lib/libnova/src/comet.c \
  ../lib/libnova/src/constellation.c \
  ../lib/libnova/src/dynamical_time.c \
  ../lib/libnova/src/earth.c \
  ../lib/libnova/src/elliptic_motion.c \
  ../lib/libnova/src/heliocentric_time.c \
  ../lib/libnova/src/hyperbolic_motion.c \
  ../lib/libnova/src/julian_day.c \
  ../lib/libnova/src/jupiter.c \
  ../lib/libnova/src/lunar.c \
  ../lib/libnova/src/mars.c \
  ../lib/libnova/src/mercury.c \
  ../lib/libnova/src/misc.c \
  ../lib/libnova/src/neptune.c \
  ../lib/libnova/src/nutation.c \
  ../lib/libnova/src/parabolic_motion.c \
  ../lib/libnova/src/parallax.c \
  ../lib/libnova/src/pluto.c \
  ../lib/libnova/src/precession.c \
  ../lib/libnova/src/proper_motion.c \
  ../lib/libnova/src/refraction.c \
  ../lib/libnova/src/rise_set.c \
  ../lib/libnova/src/saturn.c \
  ../lib/libnova/src/sidereal_time.c \
  ../lib/libnova/src/solar.c \
  ../lib/libnova/src/transform.c \
  ../lib/libnova/src/uranus.c \
  ../lib/libnova/src/utility.c \
  ../lib/libnova/src/venus.c \
  ../lib/libnova/src/vsop87.c \
  ../lib/libnova/src/elp/elp1.c \
  ../lib/libnova/src/elp/elp2.c \
  ../lib/libnova/src/elp/elp3.c \
  ../lib/libnova/src/elp/elp4.c \
  ../lib/libnova/src/elp/elp5.c \
  ../lib/libnova/src/elp/elp6.c \
  ../lib/libnova/src/elp/elp7.c \
  ../lib/libnova/src/elp/elp8.c \
  ../lib/libnova/src/elp/elp9.c \
  ../lib/libnova/src/elp/elp10.c \
  ../lib/libnova/src/elp/elp11.c \
  ../lib/libnova/src/elp/elp12.c \
  ../lib/libnova/src/elp/elp13.c \
  ../lib/libnova/src/elp/elp14.c \
  ../lib/libnova/src/elp/elp15.c \
  ../lib/libnova/src/elp/elp16.c \
  ../lib/libnova/src/elp/elp17.c \
  ../lib/libnova/src/elp/elp18.c \
  ../lib/libnova/src/elp/elp19.c \
  ../lib/libnova/src/elp/elp20.c \
  ../lib/libnova/src/elp/elp21.c \
  ../lib/libnova/src/elp/elp22.c \
  ../lib/libnova/src/elp/elp23.c \
  ../lib/libnova/src/elp/elp24.c \
  ../lib/libnova/src/elp/elp25.c \
  ../lib/libnova/src/elp/elp26.c \
  ../lib/libnova/src/elp/elp27.c \
  ../lib/libnova/src/elp/elp28.c \
  ../lib/libnova/src/elp/elp29.c \
  ../lib/libnova/src/elp/elp30.c \
  ../lib/libnova/src/elp/elp31.c \
  ../lib/libnova/src/elp/elp32.c \
  ../lib/libnova/src/elp/elp33.c \
  ../lib/libnova/src/elp/elp34.c \
  ../lib/libnova/src/elp/elp35.c \
  ../lib/libnova/src/elp/elp36.c \
  ../lib/sunriset/sunriset.c \
  ../movement.c \
  ../watch_faces/clock/simple_clock_face.c \
  ../watch_faces/clock/world_clock_face.c \
  ../watch_faces/settings/preferences_face.c \
  ../watch_faces/settings/set_time_face.c \
  ../watch_faces/complications/pulsometer_face.c \
  ../watch_faces/thermistor/thermistor_driver.c \
  ../watch_faces/thermistor/thermistor_readout_face.c \
  ../watch_faces/thermistor/thermistor_logging_face.c \
  ../watch_faces/demos/character_set_face.c \
  ../watch_faces/demos/voltage_face.c \
  ../watch_faces/demos/lis2dh_logging_face.c \
  ../watch_faces/demos/demo_face.c \
  ../watch_faces/demos/hello_there_face.c \
  ../watch_faces/complications/beats_face.c \
  ../watch_faces/complications/day_one_face.c \
  ../watch_faces/complications/stopwatch_face.c \
  ../watch_faces/complications/totp_face.c \
  ../watch_faces/complications/sunrise_sunset_face.c \
  ../watch_faces/complications/countdown_face.c \
  ../watch_faces/complications/orrery_face.c \

# Leave this line at the bottom of the file; it has all the targets for making your project.
include $(TOP)/rules.mk

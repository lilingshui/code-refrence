PROGRAM = main
SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:%.cpp=%.o)
			
INCLUDE_PATH = -I $(PWD)/build/include
TTU_INCLUDE_PATH = -I $(PWD)/ttu_src

INCLUDE_DIR = -I ./ $(INCLUDE_PATH)/ $(INCLUDE_PATH)/cjson $(INCLUDE_PATH)/dbus-1.0 $(INCLUDE_PATH)/json-c $(TTU_INCLUDE_PATH)/ $(TTU_INCLUDE_PATH)/ssl $(TTU_INCLUDE_PATH)/json_include $(TTU_INCLUDE_PATH)/include-inter $(TTU_INCLUDE_PATH)/include-rtshm $(TTU_INCLUDE_PATH)/json-c $(TTU_INCLUDE_PATH)/include			

LD_RUN_PATH = -L$(PWD)/build/lib
LDFLAGS = -ljson-c -lbase -linter -lrtshm -lparam -lgdbm -lpthread -lcontrol -lleda_sdk_c  -lcjson -ldbus-1

all: $(PROGRAM)

$(PROGRAM):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(LD_RUN_PATH) $(LDFLAGS)
	arm-linux-strip $(PROGRAM)
	@chmod 755 $(PROGRAM)
	@mv $(PROGRAM) $(PWD)/build/
	@echo "$(PROGRAM) has been compiled successfully!!!"

$(OBJS): %.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ $(INCLUDE_DIR)

clean:
	@rm -f *.o *~ $(PROGRAM)
	@rm -f $(PWD)/build/$(PROGRAM)
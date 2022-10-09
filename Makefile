passkey: passkey.h passkey.cc main.cc
	c++ -std=c++2a -O3 -Wall -Wextra -Weverything -Wno-c++98-compat -Wno-padded -flto -fno-exceptions -o passkey passkey.cc main.cc

.PHONY: clean

clean:
	rm passkey

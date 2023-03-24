# src = $(wildcard *.c)
# obj = $(patsubst %.c, %.o, $(src))

# args = -Wall -g

# ALL:a.out

# a.out: $(obj)
# 	gcc $^ -o $@ $(args)

# $(obj):%.o:%.c
# 	gcc -c $< -o $@ $(args)

# clean:
# 	-rm -rf $(obj) a.out

# .PHONY: clean ALL
clean:
	rm -rf build

git:
	@git add .
	@git commit -m "add no block ET epoll"
	@git push origin master

compile:
	@cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug
	@cmake --build build 
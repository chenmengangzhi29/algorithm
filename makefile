src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))

args = -Wall -g

ALL:a.out

a.out: $(obj)
	gcc $^ -o $@ $(args)

$(obj):%.o:%.c
	gcc -c $< -o $@ $(args)

clean:
	-rm -rf $(obj) a.out

.PHONY: clean ALL

git:
	@git add .
	@git commit -m "add epoll's ET and LT with pipe and socket"
	@git push origin master

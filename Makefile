CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= add.cgi del.cgi mod.cgi sel.cgi del_ad.cgi sel_join.cgi stu.cgi tea.cgi add_score.cgi sel_course.cgi add_course.cgi sel_ad.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
	cp *.cgi /usr/lib/cgi-bin/sx/
	cp admin.html tea.html stu.html head.html footer.html /usr/lib/cgi-bin/sx/

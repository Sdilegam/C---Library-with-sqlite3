NAME = Bookshelf.exe

CLASSES = Book

SRCSDIR = sources

SRCS = main.cpp utils.cpp ${addsuffix .cpp,${CLASSES}}

EXSRCS = sqlite3.c

vpath %.cpp ${SRCSDIR}
vpath %.cpp ${addprefix ${SRCSDIR}/,${CLASSES}}
vpath %.c external/sqlite3

OBJS =${SRCS:.cpp=.o}
LIBOBJS = ${EXSRCS:.c=.o}
CC = gcc
CPPFLAGS = ${addprefix -I${SRCSDIR}/, ${CLASSES}} -Iexternal/sqlite3 -I${SRCSDIR} -g
COMA = ,

${NAME}: ${OBJS} ${LIBOBJS}
	${CXX} ${CPPFLAGS} $^ -o ${NAME}

sqlite3: ${LIBOBJS}
	ar -rcs $@ $^

clean:
	del /Q /F ${OBJS} ${LIBOBJS} ${LIB}

fclean: clean
	del ${NAME}

re : fclean ${NAME}

run: ${NAME}
	./$^

.PHONY: clean fclean re run

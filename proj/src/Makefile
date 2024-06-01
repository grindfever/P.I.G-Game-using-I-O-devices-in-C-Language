# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/model
.PATH: ${.CURDIR}/controller

# source code files to be compiled
SRCS = proj.c board.c tile.c timer.c mouse.c keyboard.c graphics.c utils.c kbc.c menu.c game.c level.c


# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
DPADD += ${LIBLM}
DPADD += ${LIBXPM}
LDADD += -llcf -llm -lxpm


# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>

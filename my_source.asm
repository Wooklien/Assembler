TEST	START	$1000
	+LDB	#ALPHA
	BASE	ALPHA
	LDA	FIRST
	ADD	SECOND
	STA	THIRD
	ADDR	S,T
LOOP	COMP	LAST
	ADD	FIRST
	STA	LAST
	JLT	LOOP
BUFFER	RESW	1000
ALPHA	WORD	1
FIRST	WORD	-5
SECOND	WORD	10
THIRD	RESW	1
LAST	RESW	1
	END	TEST
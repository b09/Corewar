.name "Simple"
.comment ""

	st		r1, r2
	sti		r2, %:live, %1
live:
	live	%0
	ld		%12, r3
	ld		%10, r4
	ldi		r3, r4, r5
	and		r3, r4, r5
	#sub		r4, r4, r4
	zjmp	%:live

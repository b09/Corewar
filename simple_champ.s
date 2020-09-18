.name "Simple"
.comment ""

	sti		r1, %:live, %1
	sub		r1, r1, r2
fork:
	fork	%5
	fork	%0
	zjmp	%:fork
live:
	live	%0
	zjmp	%:live

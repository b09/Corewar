.name "Simple"
.comment ""

	sti		r1, %:live, %1
	live	%-1
	sub		r1, r1, r2
fork:
	fork	%9
	fork	%-3
	zjmp	%:fork
	sub		r1, r1, r2
live:
	live	%0
	zjmp	%:live

tuple_test: tuple.c tuple_test.c
	gcc tuple_test.c tuple.c -lm -o tuple_test

color_test: color_test.c color.c tuple.c 
	gcc color_test.c tuple.c -lm -o color_test


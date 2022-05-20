all:
	./build-all.sh $(filter)

clean:
	rm -f *.hex *~ *.elf *.o

todo:
	@egrep 'TODO:|FIXME:' *.[ch]

models:
	@./models.py > MODELS
	@cat MODELS

.phony: clean todo

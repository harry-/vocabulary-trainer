current

floating point exception after trying to introduce different scoresheets (and also deleting the old scoresheet "score"). Update: apparently it crashes when there is a) no score file b) the score file only has one entry. Possible solution: if linecount<2 fill scoresheet manually? UPDATE: guess the error happens in line 145: int r = rand() % probability;
update: fixed the floating point exception by setting totalProbability to 1 if its otherwise zero, but the first run (the one where the score sheet is created) is still broken
to recreate: delete scoresheet and run the program


issues

quiz.out -q 3 does not work (should it? check getopt_long documentation)

todo

create c only version (ctime is c++)
make databases chooseable (needs distinct scoresheets per db)
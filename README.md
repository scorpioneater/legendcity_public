This application in its current state was developed to quickly cut down the time needed to complete one of those awful HackerRank Spring Boot technical assessments. 
Rather than fumbling with a maze of annotations and ampersand soup, I wrote a program that spits out the boilerplate for a working Spring Boot REST application.
The code passed the default test cases on the first try. 

To generate code, run the following command (if you don't have perl installed already there is something wrong with you):

perl SpringBootFrigginSucks.pl <DSL string>

The DSL is a work in progress but here is the foundational part:

The DSL string has N numberof elements delimited by a pipe ("|").
Two types of elements are currently defined:

methods - A list of methods delimited by a comma. The items that appear after the dash ("-") are the list of arguments delimited by "&". The first letter of each argument, 
which appears before an underscore, denotes the data type of the argument. Currently only two types are supported;

     i - int
     s - String

Example output:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
$ perl cheatingWithPerl.pl "methods:getFilteredEntryById-i_initialRange&i_finalRange,getSorted-i_id"
Methods :
        getFilteredEntryById-i_initialRange&i_finalRange
        getSorted-i_id

                @GetMapping(produces = "application/json")
                        Entry getFilteredEntryById(@PathVariable int ,@PathVariable int ,){
                                return findgetFilteredEntryById(initialRange,finalRange,);
                        }

                        Entry findgetFilteredEntryById(@PathVariable int ,@PathVariable int ,) {

                        Entry entry = new Entry();

                                return new Entry();
                        }

                @GetMapping(produces = "application/json")
                        Entry getSorted(@PathVariable int ,){
                                return findgetSorted(id,);
                        }

                        Entry findgetSorted(@PathVariable int ,) {

                        Entry entry = new Entry();

                                return new Entry();
                        }



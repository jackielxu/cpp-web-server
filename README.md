# cpp-web-server
Web server in C++! This was built using Wt, a library for creating C++ web applications. The web server is made entirely in C++ and generates the related HTML and JS to support viewing on broswer.

### Requirements
* Wt (along with cmake and make)
* Boost C++ libraries (1.52+ works)
* gcc/clang

See the Wt website for more information on this. 


Usage
----

For an example file "helloworld.cpp" and executable "helloworld", compile with command:

	$ g++ -o helloworld helloworld.cpp -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time
	$ ./helloworld --docroot . --http-address 0.0.0.0 --http-port 9090

To view the application, open `0.0.0.0:9090` in browser. 

### Final Copy
To see the final copy, navigate to `master` and use the following commands on `index.cpp` and enjoy! 

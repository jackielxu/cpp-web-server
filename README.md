# cpp-web-server
Web server in C++

Usage
----

Compile with command:

	$ g++ -o helloworld helloworld.cpp -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time
	$ ./helloworld --docroot . --http-address 0.0.0.0 --http-port 9090

To view the application, open 0.0.0.0:9090 in browser. 

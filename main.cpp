/*
 * main.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: bolek
 */
/*
#include <boost/asio.hpp>
#include <iostream>

int main( void )
{
	boost::asio::io_service io_service;

	for( int x = 0; x < 42; ++x )
	{
		io_service.poll();
		std::cout << "Counter: " << x << std::endl;
	}

	return 0;
}
*/
/*
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Start";
	std::cout << std::endl;
	global_stream_lock.unlock();

	while( true )
	{
		try
		{
			boost::system::error_code ec;
			io_service->run( ec );
			if( ec )
			{
				global_stream_lock.lock();
				std::cout << "[" << boost::this_thread::get_id()
					<< "] Error: " << ec;
				std::cout << std::endl;
				global_stream_lock.unlock();
			}
			break;
		}
		catch( std::exception & ex )
		{
			global_stream_lock.lock();
			std::cout << "[" << boost::this_thread::get_id()
				<< "] Exception: " << ex.what();
			std::cout << std::endl;
			global_stream_lock.unlock();
		}
	}

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Finish";
	std::cout << std::endl;
	global_stream_lock.unlock();
}

void RaiseAnException( boost::shared_ptr< boost::asio::io_service > io_service )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] " << __FUNCTION__;
	std::cout << std::endl;
	global_stream_lock.unlock();

	io_service->post( boost::bind( &RaiseAnException, io_service ) );

	throw( std::runtime_error( "Oops!" ) );
}

int main( int argc, char * argv[] )
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
		);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work( *io_service )
		);

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] The program will exit when all work has finished.";
	std::cout << std::endl;
	global_stream_lock.unlock();

	boost::thread_group worker_threads;
	for( int x = 0; x < 2; ++x )
	{
		worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
	}

	io_service->post( boost::bind( &RaiseAnException, io_service ) );

	//io_service->stop(); // finishes all work is left on the queue before terminating io_service

	worker_threads.join_all();

	return 0;
}
*/
/*
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Start" << std::endl;
	global_stream_lock.unlock();

	while( true )
	{
		try
		{
			boost::system::error_code ec;
			io_service->run( ec );
			if( ec )
			{
				global_stream_lock.lock();
				std::cout << "[" << boost::this_thread::get_id()
					<< "] Error: " << ec << std::endl;
				global_stream_lock.unlock();
			}
			break;
		}
		catch( std::exception & ex )
		{
			global_stream_lock.lock();
			std::cout << "[" << boost::this_thread::get_id()
				<< "] Exception: " << ex.what() << std::endl;
			global_stream_lock.unlock();
		}
	}

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Finish" << std::endl;
	global_stream_lock.unlock();
}

void TimerHandler( const boost::system::error_code & error )
{
	if( error )
	{
		global_stream_lock.lock();
		std::cout << "[" << boost::this_thread::get_id()
			<< "] Error: " << error << std::endl;
		global_stream_lock.unlock();
	}
	else
	{
		global_stream_lock.lock();
		std::cout << "[" << boost::this_thread::get_id()
			<< "] TimerHandler " << std::endl;
		global_stream_lock.unlock();
	}
}

int main( int argc, char * argv[] )
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
		);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work( *io_service )
		);

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Press [return] to exit." << std::endl;
	global_stream_lock.unlock();

	boost::thread_group worker_threads;
	for( int x = 0; x < 2; ++x )
	{
		worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
	}

	boost::asio::deadline_timer timer( *io_service );
	timer.expires_from_now( boost::posix_time::seconds( 5 ) );
	timer.async_wait( TimerHandler );									// Handler is called when timer has expired or cancelled (which passes error code to it)

	std::cin.get();

	io_service->stop();

	worker_threads.join_all();

	return 0;
}
*/

/*
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Start" << std::endl;
	global_stream_lock.unlock();

	while( true )
	{
		try
		{
			boost::system::error_code ec;
			io_service->run( ec );
			if( ec )
			{
				global_stream_lock.lock();
				std::cout << "[" << boost::this_thread::get_id()
					<< "] Error: " << ec << std::endl;
				global_stream_lock.unlock();
			}
			break;
		}
		catch( std::exception & ex )
		{
			global_stream_lock.lock();
			std::cout << "[" << boost::this_thread::get_id()
				<< "] Exception: " << ex.what() << std::endl;
			global_stream_lock.unlock();
		}
	}

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Finish" << std::endl;
	global_stream_lock.unlock();
}

void TimerHandler(
	const boost::system::error_code & error,
	boost::shared_ptr< boost::asio::deadline_timer > timer
)
{
	if( error )
	{
		global_stream_lock.lock();
		std::cout << "[" << boost::this_thread::get_id()
			<< "] Error: " << error << std::endl;
		global_stream_lock.unlock();
	}
	else
	{
		global_stream_lock.lock();
		std::cout << "[" << boost::this_thread::get_id()
			<< "] TimerHandler " << std::endl;
		global_stream_lock.unlock();

		timer->expires_from_now( boost::posix_time::seconds( 5 ) );
		timer->async_wait( boost::bind( &TimerHandler, _1, timer ) );
	}
}

int main( int argc, char * argv[] )
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
	);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work( *io_service )
	);

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Press [return] to exit." << std::endl;
	global_stream_lock.unlock();

	boost::thread_group worker_threads;
	for( int x = 0; x < 2; ++x )
	{
		worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
	}

	boost::shared_ptr< boost::asio::deadline_timer > timer(
		new boost::asio::deadline_timer( *io_service )
	);
	timer->expires_from_now( boost::posix_time::seconds( 5 ) );
	timer->async_wait( boost::bind( &TimerHandler, _1, timer ) );			// Handler is called when timer has expired or cancelled (which passes error code to it)
																			// Handler is executed by any of the worker threads that have io_service->run() call
	std::cin.get();

	io_service->stop();

	worker_threads.join_all();

	return 0;
}
*/

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <iostream>

boost::mutex global_stream_lock;

void WorkerThread( boost::shared_ptr< boost::asio::io_service > io_service )
{
	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Start" << std::endl;
	global_stream_lock.unlock();

	while( true )
	{
		try
		{
			boost::system::error_code ec;
			io_service->run( ec );
			if( ec )
			{
				global_stream_lock.lock();
				std::cout << "[" << boost::this_thread::get_id()
					<< "] Error: " << ec << std::endl;
				global_stream_lock.unlock();
			}
			break;
		}
		catch( std::exception & ex )
		{
			global_stream_lock.lock();
			std::cout << "[" << boost::this_thread::get_id()
				<< "] Exception: " << ex.what() << std::endl;
			global_stream_lock.unlock();
		}
	}

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Thread Finish" << std::endl;
	global_stream_lock.unlock();
}

void TimerHandler(
	const boost::system::error_code & error,
	boost::shared_ptr< boost::asio::deadline_timer > timer,
	boost::shared_ptr< boost::asio::io_service::strand > strand
)
{
	if( error )
	{
		global_stream_lock.lock();
		std::cout << "[" << boost::this_thread::get_id()
			<< "] Error: " << error << std::endl;
		global_stream_lock.unlock();
	}
	else
	{
		std::cout << "[" << boost::this_thread::get_id()
			<< "] TimerHandler " << std::endl;

		timer->expires_from_now( boost::posix_time::seconds( 1 ) );
		timer->async_wait(
			strand->wrap( boost::bind( &TimerHandler, _1, timer, strand ) )
		);
	}
}

void PrintNum( int x )
{
	std::cout << "[" << boost::this_thread::get_id()
		<< "] x: " << x << std::endl;
	boost::this_thread::sleep( boost::posix_time::milliseconds( 1000 ) );
}

int main( int argc, char * argv[] )
{
	boost::shared_ptr< boost::asio::io_service > io_service(
		new boost::asio::io_service
	);
	boost::shared_ptr< boost::asio::io_service::work > work(
		new boost::asio::io_service::work( *io_service )
	);
	boost::shared_ptr< boost::asio::io_service::strand > strand(
		new boost::asio::io_service::strand( *io_service )
	);

	global_stream_lock.lock();
	std::cout << "[" << boost::this_thread::get_id()
		<< "] Press [return] to exit." << std::endl;
	global_stream_lock.unlock();

	boost::thread_group worker_threads;
	for( int x = 0; x < 2; ++x )
	{
		worker_threads.create_thread( boost::bind( &WorkerThread, io_service ) );
	}

	boost::this_thread::sleep( boost::posix_time::seconds( 1 ) );

	strand->post( boost::bind( &PrintNum, 1 ) );
	strand->post( boost::bind( &PrintNum, 2 ) );
	strand->post( boost::bind( &PrintNum, 3 ) );
	strand->post( boost::bind( &PrintNum, 4 ) );
	strand->post( boost::bind( &PrintNum, 5 ) );

	boost::shared_ptr< boost::asio::deadline_timer > timer(
		new boost::asio::deadline_timer( *io_service )
	);
	timer->expires_from_now( boost::posix_time::seconds( 1 ) );
	timer->async_wait(
		strand->wrap( boost::bind( &TimerHandler, _1, timer, strand ) )
	);

	std::cin.get();

	io_service->stop();

	worker_threads.join_all();

	return 0;
}



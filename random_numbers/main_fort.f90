program main

	use, intrinsic :: iso_c_binding

	implicit none


	interface
		subroutine rng_init ( ) bind ( c )
			use iso_c_binding
		end subroutine rng_init
		subroutine rng_finilize ( ) bind ( c )
			use iso_c_binding
		end subroutine rng_finilize
		subroutine randn(array, n) bind ( c )
			use iso_c_binding
			real ( c_float ) :: array(*)
			integer ( c_int ), VALUE :: n
		end subroutine randn
	end interface


	integer(c_int), parameter :: CONSUMER_SIZE = 500000

	real(c_float), dimension(CONSUMER_SIZE) :: arr_cons

	integer :: i


	call rng_init()

    call randn(arr_cons, CONSUMER_SIZE/2)

    call rng_finilize()


    do i = 1,100
    	print*, arr_cons(i)
	enddo


end program main
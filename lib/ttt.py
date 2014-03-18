def A(a = 1):
    class B:
        b = 2
        print a
        print b
        class C:
            print a
        
A()
# UNFINISHED

# When you use dotted access to look up a member (eg, x.y), 
# Python first looks for the member in the instance dictionary.
# If it's not found, it looks for it in the class dictionary.
# If it finds it in the class dictionary, and the object implements
# the descriptor protocol, instead of just returning it, Python executes 
# it. A descriptor is any class that implements the __get__, 
# __set__, or __delete__ methods.

class Property(object):
    def __init__(self, fget):
        self.fget = fget

    def __get__(self, obj, type):
        if obj is None:
            return self
        return self.fget(obj)

class MyClass(object):
    @Property
    def foo(self):
        return "Foo!"
x = MyClass()
print x.foo()

# Sources
# http://stackoverflow.com/questions/101268/hidden-features-of-python#102062
# http://users.rcn.com/python/download/Descriptor.htm
# http://www.gghh.name/dibtp/?p=489
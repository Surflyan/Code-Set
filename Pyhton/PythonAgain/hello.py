import math
from decimal import *

def CalQ(t,v):
    getcontext().prec=20
    a = 1.43*(10**(-14))
    c=math.sqrt(t)
    b=1+0.02*c
    d=t*b
    f=d**(3/2.0)
    print f
    g=f/float(v)
    print g
    q=Decimal(a)/Decimal(g)
    n = math.floor(Decimal(q)/ Decimal((1.60217656 * 10 **(-19))) + 0.5)
    e = float(q)/n
    print "q=%f ,n=%d,e=%f" % (q, n, e)

CalQ(42.2,317)

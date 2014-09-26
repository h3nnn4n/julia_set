import numpy

screenx=800*2
screeny=600*2

bailout=256
#~ bailout=128
#~ bailout=64

c=complex(-0.79,0.15)
#~ c=complex(-0.285,0.0)
#~ c=complex(-0.065,0.122)

real_min, real_max=-2.0,2.0
imag_min, imag_max=-2.0,2.0

real_range=numpy.arange(real_min,real_max,(real_max-real_min)/screenx)
imag_range=numpy.arange(imag_min,imag_max,(imag_max-imag_min)/screeny)

fout=open('julia.ppm','w')
#~ fout.write('P3\n'+str(screenx)+' '+str(screeny)+'\n255\n')
fout.write('P2\n'+str(screenx)+' '+str(screeny)+'\n255\n')

for im in imag_range:
    for re in real_range:
        z=complex(re,im)
        n=0
        while abs(z)<4 and n<bailout:
            #~ z=z*z+c
                z=(numpy.sin(z*z))+c
                n+=1

        #~ n=n/bailout
        #~ h=6.0*n
        #~ hi=int(h)
        #~ hf=h-hi
        #~
        #~ if hi==0:
                #~ r,g,b=1.0,hf,0.0
        #~ elif hi==1:
                #~ r,g,b=1.0-hf,1.0,0.0
        #~ elif hi==2:
                #~ r,g,b=0.0,1.0,hf
        #~ elif hi==3:
                #~ r,g,b=0.0,1.0-hf,1.0
        #~ elif hi==4:
                #~ r,g,b=hf,0.0,1.0
        #~ elif hi==5:
                #~ r,g,b=1.0,0.0,1.0-hf
        #~ else:
                #~ r,g,b=0.0,0.0,0.0
        #~
        #~ r*=255
        #~ g*=255
        #~ b*=255

        #~ fout.write(str(int(r))+' '+str(int(g))+' '+str(int(b))+' ');
        fout.write(str(n)+' ');
        fout.write('\n')
        print('Imaginary value starts in '+str(imag_min)+' and goes to '+str(imag_max)+' and is at '+str(im))
fout.close()

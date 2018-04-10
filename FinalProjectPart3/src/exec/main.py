import moldyn
import sys
import time
import yaml

if len(sys.argv) == 2:
    configfile = sys.argv[1]
else:
    print "Usage:"
    print " python %s <options filename(yaml)> " % sys.argv[0]
    exit()

# Parse the yaml config file    
f = open("config.yaml")
options = yaml.load(f)
f.close()

if 'mass' in options.keys():    
    M = options['mass']
else:
    print "options file needs to have 'mass' specified!"
    exit()

N = options['nparticles']
L = options['boxsize']
T0 = options['temp0']
h = options['stepsize']
nsteps = options['nsteps']
inputfile = options['input']
savefreq = options['savefreq']

try:
    if inputfile is None:
        Box = moldyn.ParticleBoxD(N,L,T0,M,h);
    else:
        Box = moldyn.ParticleBoxD(inputfile);
except Exception, e:
    print 'ERROR: %s' % e
    exit()

# Obtain number of times to save    
(bigSteps,addSteps) = divmod(nsteps,savefreq)    

steps = 0
t_start = time.time()
try:
    while steps<bigSteps:
        steps += 1
        Box.Solve(savefreq)
        outputfile = "solution%06d.vtk"%(steps*savefreq)
        Box.WriteData(outputfile)

    if addSteps>0:
        Box.Solve(addSteps)
        outputfile = "solution%06d.vtk"%(nsteps)    
        Box.WriteData(outputfile)

except Exception, e:
    print 'ERROR: %s' % e
    exit()
        
print "Elapsed time: ", time.time() - t_start, "seconds"

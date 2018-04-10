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
f = open(configfile)
options = yaml.load(f)
f.close()
keyset = set(options.keys())

# Parse 'input' argument
if 'input' in keyset:
    inputfile = options['input']
    keyset.discard('input')
else:
    inputfile = None

# Parse 'output' argument    
if 'output' in keyset:
    outputfile = options['output']
    locq = outputfile.find('?')
    locd = outputfile.find('.')
    prefix = outputfile[0:locq]
    suffix = outputfile[locd:]
    keyset.discard('output')
else:
    prefix = "solution"
    suffix = ".vtk"
    print "Warning: output file not specified, solution??????.vtk convention will be used!"

# Parse 'nsteps' and 'savefreq'
if 'savefreq' in keyset:
    savefreq = options['savefreq']
    keyset.discard('savefreq')
else:
    print 'ERROR: save frequency not specified'
    exit()
    
if 'nsteps' in keyset:
    nsteps = options['nsteps']
    keyset.discard('nsteps')
else:
    print 'ERROR: save frequency not specified'
    exit()

# Check if 'precision' is specified
if 'precision' in keyset:
    prec = options['precision']
else:
    prec = 'double'

# Generate handle for contructor based on precision    
if prec == 'double':
    ParticleBox = moldyn.ParticleBoxD
elif prec == 'float':
    ParticleBox = moldyn.ParticleBoxF
else:
    print "ERROR: Invalid precision type: '%s'"%prec
    exit()
    
# Initialize Molecular Dynamics simulation        
if inputfile:
    try:
        Box = ParticleBox(inputfile)
    except Exception, e:
        print 'ERROR: %s' % e
        exit()
else:
    expectedParam = {'mass','nparticles','boxsize','temp0','stepsize'}
    notSpecifiedParam = expectedParam.difference(keyset)
    if len(notSpecifiedParam) != 0:
        print "ERROR: %s is/are not specified" % notSpecifiedParam
        exit()
        
    M = options['mass']
    N = options['nparticles']
    L = options['boxsize']
    T0 = options['temp0']
    h = options['stepsize']

    try:
        print "Warning: input file not specified, random initialization will be used"
        Box = ParticleBox(N,L,T0,M,h)
    except Exception, e:
        print 'ERROR: %s' % e
        exit()

# Obtain number of times to save    
(bigSteps,addSteps) = divmod(nsteps,savefreq)    

# Perform the solve and save as specified 
steps = 0
t_start = time.time()
try:
    while steps<bigSteps:
        steps += 1
        currentStep = Box.Solve(savefreq)
        outputfile = prefix + "%06d"%(currentStep) + suffix
        Box.SaveOutput(outputfile)

    if addSteps>0:
        currentStep = Box.Solve(addSteps)
        outputfile = prefix + "solution%06d.vtk"%(currentStep) + suffix 
        Box.SaveOutput(outputfile)
except Exception, e:
    print 'ERROR: %s' % e
    exit()
        
print "Elapsed time: ", time.time() - t_start, "seconds"

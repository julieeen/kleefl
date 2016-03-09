
version_no=3
class KTestError(Exception):
	 pass

class KTest:
	@staticmethod
	def fromfile(path):
		if not os.path.exists(path):
			print("ERROR: file %s not found" % (path))
			sys.exit(1)
			
		f = open(path,'rb')
		hdr = f.read(5)
		if len(hdr)!=5 or (hdr!=b'KTEST' and hdr != b"BOUT\n"):
			raise KTestError('unrecognized file')
		version, = struct.unpack('>i', f.read(4))
		if version > version_no:
			raise KTestError('unrecognized version')
		numArgs, = struct.unpack('>i', f.read(4))
		args = []
		for i in range(numArgs):
			size, = struct.unpack('>i', f.read(4))
			args.append(str(f.read(size).decode(encoding='ascii')))
			
		if version >= 2:
			symArgvs, = struct.unpack('>i', f.read(4))
			symArgvLen, = struct.unpack('>i', f.read(4))
		else:
			symArgvs = 0
			symArgvLen = 0

		numObjects, = struct.unpack('>i', f.read(4))
		objects = []
		for i in range(numObjects):
			size, = struct.unpack('>i', f.read(4))
			name = f.read(size)
			size, = struct.unpack('>i', f.read(4))
			bytes = f.read(size)
			objects.append( (name,bytes) )

		# Create an instance
		b = KTest(version, args, symArgvs, symArgvLen, objects)
		# Augment with extra filename field
		b.filename = path
		return b

	def __init__(self, version, args, symArgvs, symArgvLen, objects):
		self.version = version
		self.symArgvs = symArgvs
		self.symArgvLen = symArgvLen
		self.args = args
		self.objects = objects

		# add a field that represents the name of the program used to
		# generate this .ktest file:
		program_full_path = self.args[0]
		program_name = os.path.basename(program_full_path)
		# sometimes program names end in .bc, so strip them
		if program_name.endswith('.bc'):
		 program_name = program_name[:-3]
		self.programName = program_name
#header()

#ifndef OI_H
\#define OI_H

\#include "WPILib.h"

class OI {
private:
#@autogenerated_code("declarations", "	")
#parse("${exporter-path}OI-declarations.h")
#end
public:
	OI();
 
#@autogenerated_code("prototypes", "	")
#parse("${exporter-path}OI-prototypes.h")
#end
};

#endif

/*
 *  Author: bwilliams
 *  Created: April 6, 2012
 *
 *  Copyright (c) 2012 Vmware, Inc.  All rights reserved.
 *  -- VMware Confidential
 *
 *  This code was generated by the script "build/dev/codeGen/genCppXml". Please
 *  speak to Brian W. before modifying it by hand.
 *
 */

#ifndef DataClassInstanceCollectionXml_h_
#define DataClassInstanceCollectionXml_h_

namespace Caf {

	/// Streams the DataClassInstanceCollection class to/from XML
	namespace DataClassInstanceCollectionXml {

		/// Adds the DataClassInstanceCollectionDoc into the XML.
		void SCHEMATYPESXML_LINKAGE add(
			const SmartPtrCDataClassInstanceCollectionDoc dataClassInstanceCollectionDoc,
			const SmartPtrCXmlElement thisXml);

		/// Parses the DataClassInstanceCollectionDoc from the XML.
		SmartPtrCDataClassInstanceCollectionDoc SCHEMATYPESXML_LINKAGE parse(
			const SmartPtrCXmlElement thisXml);
	}
}

#endif
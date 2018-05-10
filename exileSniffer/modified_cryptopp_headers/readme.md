These two headers have attributes changed to allow the internal crypt state to be accessed.
These changes are required to compile exilesniffer - you don't need to recompile the crypto++ binaries 

---- salsa.h: m_state changed from protected to public -----
class CRYPTOPP_NO_VTABLE Salsa20_Policy : public AdditiveCipherConcretePolicy<word32, 16>
{
-protected:
+public: 
	FixedSizeAlignedSecBlock<word32, 16> m_state;
	
	
---- strciphr.h: policy inherited as public instead of protected, so we can access its m_state ----
-class ConcretePolicyHolder : public BASE, protected POLICY 
+class ConcretePolicyHolder : public BASE, public POLICY 
class StringUtility
{
public:
	StringUtility(void);
	~StringUtility(void);

	static constexpr unsigned int str2int(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
	}

	template<class T>
	static T base_name(T const & path, T const & delims = "/\\")
	{
	  return path.substr(path.find_last_of(delims) + 1);
	}
	template<class T>
	static T parent_path(T const & path, T const & delims = "/\\")
	{
	  return path.substr(0,path.find_last_of(delims));
	}
	template<class T>
	static T remove_extension(T const & filename)
	{
	  typename T::size_type const p(filename.find_last_of('.'));
	  return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
	}
};
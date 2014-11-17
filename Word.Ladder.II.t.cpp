#include "Word.Ladder.II.cpp"

int main()
{
    char p_dict[][4] = {
        "ted",
        "tex",
        "red",
        "tax",
        "tad",
        "den",
        "rex",
        "pee"
    };
    std::string start( "red" );
    std::string end( "tax" );
    std::unordered_set< std::string >
        dict( p_dict, p_dict + sizeof( p_dict ) / sizeof( p_dict[ 0 ] ) );
    
    Solution sln;
    std::vector< std::vector< std::string > > results
        = sln.findLadders( start, end, dict );
    
    for ( const auto & ladder : results )
    {
        for ( const auto & w : ladder )
            std::cout << w << ", ";

        std::cout << std::endl;
    }

    return 0;
}


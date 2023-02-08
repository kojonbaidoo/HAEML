library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library work;
use work.configuration_pack.all;

entity output_comparator is
 Port ( 
    clk: in std_logic;
    layer_6_out_array: in layer_6_out;
    result: out std_logic_vector(1 downto 0)
 );
end output_comparator;

architecture Behavioral of output_comparator is
    signal result_signal: std_logic_vector(1 downto 0);

begin

    result <=   "01" when (layer_6_out_array(0) > layer_6_out_array(1) and layer_6_out_array(0) > layer_6_out_array(2)) else
                "10" when (layer_6_out_array(1) > layer_6_out_array(0) and layer_6_out_array(1) > layer_6_out_array(2)) else
                -- "11" when (layer_6_out_array(2) > layer_6_out_array(1) and layer_6_out_array(2) > layer_6_out_array(1)) else
                "11" when (layer_6_out_array(2) >= "0000000000000000") else
                "00" ;
    
end Behavioral;

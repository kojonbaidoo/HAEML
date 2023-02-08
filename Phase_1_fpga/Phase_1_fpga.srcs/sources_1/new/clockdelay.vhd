----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 15.05.2022 19:23:13
-- Design Name: 
-- Module Name: clockdelay - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity clockdelay is
    Port (CLK:in std_logic;
          osCLK:out std_logic);
end clockdelay;

architecture Behavioral of clockdelay is
signal c:std_logic:='1';

begin
    myclock:process(CLK)
    variable count: natural range 0 to 100000;
        begin
            if(rising_edge(CLK)) then
                if(count = 100000) then
                    count := 0;
                    c <= not c;
                else
                    count := count + 1;
                end if;
            end if;
            osCLK <= c;
        end process myclock;
end Behavioral;

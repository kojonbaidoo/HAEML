library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity communication_module is
    port(
        clk : in std_logic;
        mcu_data : in std_logic_vector(7 downto 0);
        mcu_signal : in std_logic;
        mcu_ready : in std_logic;

        fpga_signal : out std_logic;
        fpga_data : out std_logic_vector(1 downto 0);
        fpga_ready : out std_logic;

        input_1_data : out std_logic_vector(15 downto 0);
        input_2_data : out std_logic_vector(15 downto 0);
        input_3_data : out std_logic_vector(15 downto 0);

        nn_out_data : in std_logic_vector(1 downto 0);
        nn_done : in std_logic;
        input_count : out std_logic_vector(2 downto 0)
    );
end communication_module;


architecture rtl of communication_module is
    signal input_data_reg : std_logic_vector(7 downto 0);
    signal output_data_reg : std_logic_vector(1 downto 0) := "01";
    
    signal mcu_signal_buffer : std_logic;
    signal mcu_ready_buffer : std_logic;

    signal fpga_signal_next : std_logic := '1';
    signal fpga_ready_signal : std_logic := '1';

    signal count : std_logic_vector(2 downto 0) := "000";
begin
    fpga_ready <= fpga_ready_signal;
    fpga_signal <= fpga_signal_next;
    input_count <= count;
    
  -- Testing 
    process(clk)
    begin
        if rising_edge(clk) then
            if mcu_ready = '1' and mcu_ready_buffer = '0' then
                -- reset communication module
                count <= "000";
                fpga_signal_next <= '1';
                input_1_data <= "0000000000000000";
                input_2_data <= "0000000000000000";
                input_3_data <= "0000000000000000";
                fpga_ready_signal <= '1'; -- reset fpga_ready_signal to high
            elsif mcu_signal = '1' and mcu_signal_buffer = '0' then
                -- set fpga_signal_next to 0 on rising edge of mcu_signal
                fpga_signal_next <= '0';
            elsif fpga_signal_next = '0' and mcu_signal = '1' and mcu_signal_buffer = '1' then
                -- read input data and increment count when fpga_signal_next is 0
                case count is
                    when "000" =>
                        input_data_reg <= mcu_data;
                        count <= "001";
                    when "001" =>
                        input_1_data <= mcu_data & input_data_reg;
                        count <= "010";
                    when "010" =>
                        input_data_reg <= mcu_data;
                        count <= "011";
                    when "011" =>
                        input_2_data <= mcu_data & input_data_reg;
                        count <= "100";
                    when "100" =>
                        input_data_reg <= mcu_data;
                        count <= "101";
                    when "101" =>
                        input_3_data <= mcu_data & input_data_reg;
                        fpga_ready_signal <= '0';
                        count <= "110";
                    when others =>
                        -- do nothing
                end case;
                fpga_signal_next <= '1';
            end if;
    
            if nn_done = '1' and fpga_ready_signal = '0' and count = "110" then
                fpga_data <= nn_out_data;
                fpga_ready_signal <= '1';
                -- Should end up clearing nn_done
            end if;
    
            -- update signal buffers
            mcu_signal_buffer <= mcu_signal;
            mcu_ready_buffer <= mcu_ready;
        end if;
    end process;
  
--    process(clk)
--    begin
--        if rising_edge(clk) then
--            mcu_signal_buffer <= mcu_signal;
--            mcu_ready_buffer <= mcu_ready;
--        end if;

--        if rising_edge(clk) then
--            -- reset communication module
--            if mcu_ready = '1' and mcu_ready_buffer = '0' then
--                count <= "000";
--                fpga_signal_next <= '1';
--                input_1_data <= "0000000000000000"; 
--                input_2_data <= "0000000000000000";  
--                input_3_data <= "0000000000000000";  
    
--            elsif mcu_ready = '1' and mcu_ready_buffer ='1' and fpga_ready_signal = '1' then
----                if fpga_signal_next = '1' and mcu_signal = '1' and mcu_signal_buffer = '0' then
--                if mcu_signal = '1' and mcu_signal_buffer = '0' then
--                    fpga_signal_next <= '0';
        
--                elsif fpga_signal_next = '0' and mcu_signal = '1' and mcu_signal_buffer = '1' then
                    
--                    if count = "100" then
--                        input_data_reg <= mcu_data;
--                        count <= count + 1;
--                        fpga_signal_next <= '1';
                            
--                    elsif count = "001" then
--                        input_1_data <= mcu_data & input_data_reg;
--                        count <= count + 1;
--                        fpga_signal_next <= '1';
                    
--                    elsif count = "010" then
--                        input_data_reg <= mcu_data;
--                        count <= count + 1;
--                        fpga_signal_next <= '1';
        
--                    elsif count = "011" then
--                        input_2_data <= mcu_data & input_data_reg;
--                        count <= count + 1;
--                        fpga_signal_next <= '1';
                    
--                    elsif count = "100" then
--                        input_data_reg <= mcu_data;
--                        count <= count + 1;
--                        fpga_signal_next <= '1';
        
--                    elsif count = "101" then
--                        input_3_data <= mcu_data & input_data_reg;
--                        count <= count + 1;
--                        fpga_ready_signal <= '0';
--                        fpga_signal_next <= '1';
--                    end if;
--                end if;
--            end if;
            
--            if nn_done = '1' and fpga_ready_signal = '0' and count = "110" then
--                fpga_data <= nn_out_data;
--                fpga_ready_signal <= '1';
--                -- Should end up clearing nn_done
--            end if;
        
--        end if;
--    end process;


end rtl;

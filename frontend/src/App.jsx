import { useState, useEffect } from 'react';
import axios from 'axios';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ResponsiveContainer } from 'recharts';

export default function App() {
  const [telemetry, setTelemetry] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get('http://127.0.0.1:8000/api/telemetry/live/');
        // Reverse the array so the graph plots left-to-right (oldest to newest)
        setTelemetry(response.data.reverse());
      } catch (error) {
        console.error("Error fetching data:", error);
      }
    };
    
    fetchData();
    const interval = setInterval(fetchData, 1000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div style={{ padding: '20px', fontFamily: 'sans-serif', maxWidth: '1000px', margin: '0 auto' }}>
      <h2>Live Machine Diagnostics</h2>
      
      <div style={{ height: '400px', marginBottom: '40px', backgroundColor: '#f9f9f9', padding: '20px', borderRadius: '8px' }}>
        <ResponsiveContainer width="100%" height="100%">
          <LineChart data={telemetry}>
            <CartesianGrid strokeDasharray="3 3" />
            <XAxis dataKey="timestamp" tick={false} />
            <YAxis domain={[-15, 15]} />
            <Tooltip />
            <Legend />
            <Line type="monotone" dataKey="x_axis" stroke="#8884d8" dot={false} isAnimationActive={false} />
            <Line type="monotone" dataKey="y_axis" stroke="#82ca9d" dot={false} isAnimationActive={false} />
            <Line type="monotone" dataKey="z_axis" stroke="#ffc658" dot={false} isAnimationActive={false} />
          </LineChart>
        </ResponsiveContainer>
      </div>

      <div style={{ display: 'grid', gap: '10px' }}>
        {/* Re-reverse the data for the list view so newest is on top */}
        {[...telemetry].reverse().slice(0, 10).map((log) => (
          <div key={log.id} style={{ 
            padding: '15px', 
            backgroundColor: log.machine_status === 'FAULTY' ? '#ffebee' : '#e8f5e9',
            borderLeft: `5px solid ${log.machine_status === 'FAULTY' ? '#f44336' : '#4caf50'}`,
            borderRadius: '4px'
          }}>
            <strong>{log.machine_status}</strong> | X: {log.x_axis} | Y: {log.y_axis} | Z: {log.z_axis} | Freq: {log.dominant_freq}Hz | Amp: {log.peak_amplitude?.toFixed(2)}
          </div>
        ))}
      </div>
    </div>
  );
}
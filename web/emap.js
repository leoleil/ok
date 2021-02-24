
var dom = document.getElementById("container");
var myChart = echarts.init(dom);
var app = {};
var option = null;
var bmapModel = null;
var nodeData = []; //{name: 'node1', value:[114.31,30.52,100]},{name: 'node2', value: [115.480656,35.23375,100]}
var lineData = []; //{fromName: 'node1',toName: 'node2',coords: [[114.31,30.52,100], [115.480656,35.23375,100]]}
var context;
// 初始化Qt连接
function init()
{
    if (typeof qt != 'undefined')
    {
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
            context = channel.objects.bmapBridge;
        }
        );
    }
    else
    {
        alert("qt对象获取失败！");
    }
}

init();
// 地图默认配置
var bmap = {
    center: [104.114129, 37.550339],
    zoom: 6,
    roam: true
}
// 节点样式配置
var node = {
    name: '交换节点',
    type: 'effectScatter',
    coordinateSystem: 'bmap',
    data: nodeData,
    symbolSize: 15,
    encode: {
        value: 2
    },
    label: {
        show: true,
        position: 'top',
        formatter: '{b}'
    },
    showEffectOn: 'render',
    rippleEffect: {
        brushType: 'stroke'
    },
    hoverAnimation: true,
    itemStyle: {
        color: '#0099CC',
        shadowBlur: 10,
        shadowColor: '#99CCFF'
    },
    emphasis: {
        label: {
            show: true
        }
    },
    tooltip:{
        formatter: '{b}: [{c}]'
    },
    zlevel: 1
}
// 虚拟节点样式
var v_node = {
    name: '虚拟节点',
    type: 'effectScatter',
    coordinateSystem: 'bmap',
    data: nodeData,
    symbolSize: 15,
    encode: {
        value: 2
    },
    label: {
        show: true,
        position: 'top',
        formatter: '{b}'
    },
    showEffectOn: 'render',
    rippleEffect: {
        brushType: 'stroke'
    },
    hoverAnimation: true,
    itemStyle: {
        color: '#9F81F7',
        shadowBlur: 10,
        shadowColor: '#9F81F7'
    },
    emphasis: {
        label: {
            show: true
        }
    },
    tooltip:{
        formatter: '虚拟节点{b}: [{c}]'
    },
    zlevel: 1
}
// 线样式配置
var line = {
    name: '光纤链路',
    type: 'lines',
    coordinateSystem: 'bmap',
    polyline: true,
    large: true,
    effect: {
        show: true,
        period: 6,
        trailLength: 0.7,
        color: '#fff',
        symbolSize: 3
    },
    lineStyle: {
        color: '#0099CC',
        width: 3,
        curveness:0
    },
    zlevel: 0,
    data: lineData
}
// 虚拟链路样式
var v_line = {
    name: '虚拟链路',
    type: 'lines',
    coordinateSystem: 'bmap',
    large: true,
    effect: {
        show: true,
        color: '#fff',
    },
    lineStyle: {
        color: '#9F81F7',
        width: 1
    },
    zlevel: 0,
    data: []
}
option = {
    tooltip: {
        trigger: 'item'
    },
    legend: {
        data: [{
            name: '交换节点'
        },{
            name: '光纤链路'
        },{
            name: '虚拟节点'
        },{
            name: '虚拟链路'
        }]
    },
    bmap: bmap,
    series: [
        node,
        line,
        v_node,
        v_line
    ]
};
if (option && typeof option === "object") {
    myChart.setOption(option, true);
}

//  百度地图样式配置
styleJson = [{
    "featureType": "land",
    "elementType": "geometry",
    "stylers": {
        "color": "#fffff9ff"
    }
}, {
    "featureType": "water",
    "elementType": "geometry",
    "stylers": {
        "color": "#69b0acff"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#94ad79ff"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "arterial",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#d4e2c6ff"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#d4e2c6ff"
    }
}, {
    "featureType": "provincialway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#d4e2c6ff"
    }
}, {
    "featureType": "provincialway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "tertiaryway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "tertiaryway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "fourlevelway",
    "elementType": "geometry.fill",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "fourlevelway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "subway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "railway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "highwaysign",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "highwaysign",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "nationalwaysign",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "nationalwaysign",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "provincialwaysign",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "provincialwaysign",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "tertiarywaysign",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "tertiarywaysign",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "subwaylabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "subwaylabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#94ad79ff"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "arterial",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#b5caa0ff"
    }
}, {
    "featureType": "highway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "highway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "highway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "highway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "highway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "highway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "highway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "highway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "highway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "nationalway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "nationalway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "nationalway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "nationalway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "nationalway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "nationalway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "nationalway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "nationalway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "nationalway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "provincialway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "8,9",
        "level": "8"
    }
}, {
    "featureType": "provincialway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "8,9",
        "level": "9"
    }
}, {
    "featureType": "provincialway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "8,9",
        "level": "8"
    }
}, {
    "featureType": "provincialway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "8,9",
        "level": "9"
    }
}, {
    "featureType": "provincialway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "8,9",
        "level": "8"
    }
}, {
    "featureType": "provincialway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "8,9",
        "level": "9"
    }
}, {
    "featureType": "cityhighway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "cityhighway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "cityhighway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "cityhighway",
    "stylers": {
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "geometry",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "6"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "7"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "8"
    }
}, {
    "featureType": "cityhighway",
    "elementType": "labels",
    "stylers": {
        "visibility": "off",
        "curZoomRegionId": "0",
        "curZoomRegion": "6,9",
        "level": "9"
    }
}, {
    "featureType": "entertainment",
    "elementType": "geometry",
    "stylers": {
        "color": "#e4f0d7ff"
    }
}, {
    "featureType": "manmade",
    "elementType": "geometry",
    "stylers": {
        "color": "#effcf0ff"
    }
}, {
    "featureType": "education",
    "elementType": "geometry",
    "stylers": {
        "color": "#e3f7e4ff"
    }
}, {
    "featureType": "building",
    "elementType": "geometry.stroke",
    "stylers": {
        "color": "#a1cfa4ff"
    }
}, {
    "featureType": "poilabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "poilabel",
    "elementType": "labels.icon",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "education",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#7a7a7aff"
    }
}, {
    "featureType": "education",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "education",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": 26
    }
}, {
    "featureType": "manmade",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#afafafff"
    }
}, {
    "featureType": "manmade",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": 26
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#376b6dff"
    }
}, {
    "featureType": "scenicspots",
    "elementType": "labels",
    "stylers": {
        "visibility": "off"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "on"
    }
}, {
    "featureType": "scenicspotslabel",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff",
        "weight": 4
    }
}, {
    "featureType": "country",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#376b6dff"
    }
}, {
    "featureType": "country",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffffff",
        "weight": 3
    }
}, {
    "featureType": "water",
    "elementType": "labels.text.fill",
    "stylers": {
        "color": "#ffffffff"
    }
}, {
    "featureType": "water",
    "elementType": "labels.text.stroke",
    "stylers": {
        "color": "#ffffff00"
    }
}, {
    "featureType": "water",
    "elementType": "labels.text",
    "stylers": {
        "fontsize": 24
    }
}, {
    "featureType": "districtlabel",
    "elementType": "labels",
    "stylers": {
        "visibility": "on"
    }
}];
// 获取百度地图模型对象
bmapModel = myChart.getModel().getComponent('bmap').getBMap();
bmapModel.setMapStyle({
    styleJson: styleJson
});
// 添加节点
var addNode = function (params) {
    var n = {
        name: '节点' + nodeData.length,
        value: [params.point.lng, params.point.lat]
    }
    if(typeof context == 'undefined')
    {
        alert("context对象获取失败！");
    }
    else
    {
        context.createNode(n.name, params.point.lng, params.point.lat);
    }
    nodeData.push(n);
    option = myChart.getOption();
    option.series[0].data = nodeData;
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 百度地图双击添加节点
bmapModel.addEventListener('dblclick', addNode);

// 锚点对象
var anchor = {
    haveChoose: false,
    data: {
        name: 'node1',
        value: [114.31, 30.52, 100]
    },
    dataIndex: 0
}
// 绘线
var paintLine = (params) => {
    //console.log(anchor);
    if (anchor.haveChoose) {
        option = myChart.getOption();
        lineData = option.series[1].data;
        lineData[lineData.length - 1].coords[1] = [params.point.lng, params.point.lat];
        option.series[1].data = lineData;
        myChart.setOption(option, true);
        bmapModel = myChart.getModel().getComponent('bmap').getBMap();
        bmapModel.addEventListener('dblclick', addNode);
        bmapModel.setMapStyle({
            styleJson: styleJson
        });
        bmapModel.addEventListener('mousemove', paintLine);
        bmapModel.addEventListener('rightclick', cancelAnchor);
    }
}
// 取消锚点
var cancelAnchor = ()=>{
    console.log("取消锚点");
    anchor.haveChoose = false;
    option = myChart.getOption();
    option.series[1].data.pop();
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 百度地图移动监听
bmapModel.addEventListener('mousemove', paintLine);
bmapModel.addEventListener('rightclick', cancelAnchor);
// 落锚点
var dropAnchor = (params) => {
    if (params.componentType == "series" && params.componentSubType == "effectScatter") {
        console.log(params);
        if (!anchor.haveChoose) {
            anchor.haveChoose = true;
            anchor.data = params.data;
            anchor.dataIndex = params.dataIndex;
            option = myChart.getOption();
            //console.log(option.series[1]);
            option.series[1].data.push({
                name: anchor.data.name,
                fromName: anchor.data.name,
                toName: 'node2',
                coords: [
                    [anchor.data.value[0], anchor.data.value[1]],
                    [anchor.data.value[0], anchor.data.value[1]]
                ]
            });
            myChart.setOption(option, true);
            bmapModel = myChart.getModel().getComponent('bmap').getBMap();
            bmapModel.addEventListener('dblclick', addNode);
            bmapModel.setMapStyle({
                styleJson: styleJson
            });
            bmapModel.addEventListener('mousemove', paintLine);
            bmapModel.addEventListener('rightclick', cancelAnchor);
        } else {
            anchor.haveChoose = false;
            option = myChart.getOption();
            lineData = option.series[1].data;
            lineData[lineData.length - 1].coords[1] = [params.data.value[0], params.data.value[1]];
            lineData[lineData.length - 1].toName = params.data.name;
            lineData[lineData.length - 1].name = lineData[lineData.length - 1].fromName + '-' + lineData[lineData.length - 1].toName;
            // 计算两点间距离
            length = caculateLL(lineData[lineData.length - 1].coords[0][0],lineData[lineData.length - 1].coords[0][1],
                lineData[lineData.length - 1].coords[1][0], lineData[lineData.length - 1].coords[1][1]);
            option.series[1].data = lineData;
            myChart.setOption(option, true);
            bmapModel = myChart.getModel().getComponent('bmap').getBMap();
            bmapModel.addEventListener('dblclick', addNode);
            bmapModel.setMapStyle({
                styleJson: styleJson
            });
            bmapModel.addEventListener('mousemove', paintLine);
            bmapModel.addEventListener('rightclick', cancelAnchor);
            if(typeof context == 'undefined')
            {
                alert("context对象获取失败！");
            }
            else
            {
                context.createFiberLink('链路' + lineData.length, anchor.dataIndex, params.dataIndex, 1, length);
            }
        }
    }
}
// echarts对象单击节点事件监听
myChart.on('click', (params) => {
    console.log(params);
    if (params.componentType == "series" && params.componentSubType == "effectScatter") {
        dropAnchor(params);// 落下锚点
    }
});
// 接收qt的更新Nodes请求
function upDateNodes(params){
    option = myChart.getOption();
    nodeData = params;
    option = myChart.getOption();
    option.series[0].data = nodeData;
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 接收qt的更新链路的请求
function upDateLinks(params){
    lineData = params;
    option = myChart.getOption();
    option.series[1].data = lineData;
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 接收qt更新的虚拟节点请求
function upDateVNodes(params){
    option = myChart.getOption();
    nodeData = params;
    option = myChart.getOption();
    option.series[2].data = nodeData;
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 接收qt更新的虚拟链路请求
function upDateVLinks(params){
    lineData = params;
    option = myChart.getOption();
    option.series[3].data = lineData;
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 以追加的方式添加虚拟链路
function addEndDateVLinks(params){
    option = myChart.getOption();
    for(j = 0,len=params.length; j < len; j++) {
        option.series[3].data.push(params[j]);
    }
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 清理虚拟链路
function vLinksClear(params){
    option = myChart.getOption();
    option.series[3].data = [];
    myChart.setOption(option, true);
    bmapModel = myChart.getModel().getComponent('bmap').getBMap();
    bmapModel.addEventListener('dblclick', addNode);
    bmapModel.setMapStyle({
        styleJson: styleJson
    });
    bmapModel.addEventListener('mousemove', paintLine);
    bmapModel.addEventListener('rightclick', cancelAnchor);
}
// 计算两点间距离
function caculateLL(lat1, lng1, lat2, lng2) {
    var radLat1 = lat1 * Math.PI / 180.0;
    var radLat2 = lat2 * Math.PI / 180.0;
    var a = radLat1 - radLat2;
    var b = lng1 * Math.PI / 180.0 - lng2 * Math.PI / 180.0;
    var s = 2 * Math.asin(Math.sqrt(Math.pow(Math.sin(a / 2), 2) + Math.cos(radLat1) * Math.cos(radLat2) * Math.pow(Math.sin(b / 2), 2)));
    s = s * 6378.137;
    s = Math.round(s * 10000) / 10;
    return s / 1000;
}

import{r as d,o as c,c as l,a as s,t as p,u as E,b as g,d as m,e as R,p as v,f as u}from"./index.3256385d.js";import{S,C,P as I,G as Q,O as A,W as x,a as D}from"./OrbitControls.e5eb6b91.js";import{_ as V}from"./_plugin-vue_export-helper.cdc0426e.js";const w="/assets/icon_mokuaihua_nor.4ee7265d.png",B="/assets/icon_kongzhi_nor.5631d699.png",M="data:image/png;base64,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",K="/assets/icon_safe_nor.eba40b75.png",F="/assets/icon_state_nor.3c0d433f.png";class H{constructor(e){this.canvas=e,this.sizes={},this.camera=null,this.renderer=null,this.scene=new S,this.clock=new C,this.previousTime=0,this.initWindowSizes(),this.initcamera(),this.initHelper(),this.initControls(),this.initRenderer(),this.initAnimateTick()}initWindowSizes(){const e={width:this.canvas.parentNode.clientWidth,height:this.canvas.parentNode.clientHeight};window.addEventListener("resize",()=>{e.width=this.canvas.parentNode.clientWidth,e.height=this.canvas.parentNode.clientHeight,this.camera.aspect=e.width/e.height,this.camera.updateProjectionMatrix(),this.renderer.setSize(e.width,e.height),this.renderer.setPixelRatio(Math.min(window.devicePixelRatio,2))}),this.sizes=e}initcamera(){const e=new I(75,this.sizes.width/this.sizes.height,.1,100);e.position.set(0,5,10),this.scene.add(e),this.camera=e}initHelper(){const e=new Q(100,50,"#D8D8D8","#D8D8D8");this.scene.add(e)}initControls(){const e=new A(this.camera,this.canvas);e.target.set(0,0,0),e.enableDamping=!0,this.controls=e,this.controls.enabled=!1}initRenderer(){this.renderer=new x({canvas:this.canvas}),this.renderer.shadowMap.enabled=!0,this.renderer.shadowMap.type=D,this.renderer.setSize(this.sizes.width,this.sizes.height),this.renderer.setPixelRatio(Math.min(window.devicePixelRatio,2)),this.renderer.setClearColor("#fff")}initAnimateTick(){const e=this.clock.getElapsedTime();e-this.previousTime,this.previousTime=e,this.controls.update(),this.renderer.render(this.scene,this.camera),window.requestAnimationFrame(()=>{this.initAnimateTick()})}}const i=n=>(v("data-v-25df223d"),n=n(),u(),n),N={class:"main-container"},f={class:"middle"},P=i(()=>s("canvas",{class:"Base3d"},null,-1)),O={class:"bottom"},y=i(()=>s("h2",{style:{"text-align":"center"}},"\u7F16\u7A0B",-1)),j=i(()=>s("h2",{style:{"text-align":"center"}},"\u63A7\u5236\u6A21\u5F0F",-1)),T=i(()=>s("h2",{style:{"text-align":"center"}},"\u4E3B\u9875",-1)),k=i(()=>s("h2",{style:{"text-align":"center"}},"\u7CFB\u7EDF\u5B89\u5168",-1)),G=i(()=>s("h2",{style:{"text-align":"center"}},"\u7CFB\u7EDF\u72B6\u6001",-1)),J={setup(n){const e=g();m();const h=d({base3d:{},socketLink:{}});c(async()=>{h.base3d=new H(document.querySelector("canvas.Base3d"))});const a=r=>{e.push(r)};return(r,t)=>(R(),l("div",N,[s("div",f,[s("h2",null,p(E(h).currentRouter),1),P]),s("div",O,[s("div",null,[s("img",{class:"mokuaihua",src:w,alt:"",onClick:t[0]||(t[0]=o=>a("/program"))}),y]),s("div",null,[s("img",{class:"kongzhi",src:B,alt:"",onClick:t[1]||(t[1]=o=>a("/control"))}),j]),s("div",null,[s("img",{class:"home",src:M,alt:"",onClick:t[2]||(t[2]=o=>a("/home"))}),T]),s("div",null,[s("img",{class:"safe",src:K,alt:"",onClick:t[3]||(t[3]=o=>a("/safety"))}),k]),s("div",null,[s("img",{class:"state",src:F,alt:"",onClick:t[4]||(t[4]=o=>a("/status"))}),G])])]))}},U=V(J,[["__scopeId","data-v-25df223d"]]);export{U as default};
